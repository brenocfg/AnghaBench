#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct irq_domain {int dummy; } ;
struct device {struct device* parent; } ;
struct TYPE_3__ {scalar_t__ region_count; int /*<<< orphan*/  id; } ;
struct fsl_mc_device {int /*<<< orphan*/ * mc_io; struct device dev; int /*<<< orphan*/  mc_handle; TYPE_1__ obj_desc; TYPE_2__* regions; } ;
struct fsl_mc_bus {int /*<<< orphan*/  scan_mutex; int /*<<< orphan*/  dprc_attr; } ;
struct TYPE_4__ {int /*<<< orphan*/  start; } ;

/* Variables and functions */
 scalar_t__ DPRC_MIN_VER_MAJOR ; 
 scalar_t__ DPRC_MIN_VER_MINOR ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  FSL_MC_IO_ATOMIC_CONTEXT_PORTAL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__,...) ; 
 struct irq_domain* dev_get_msi_domain (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*) ; 
 scalar_t__ dev_is_fsl_mc (struct device*) ; 
 int /*<<< orphan*/  dev_set_msi_domain (struct device*,struct irq_domain*) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int /*<<< orphan*/  dprc_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dprc_get_api_version (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int dprc_get_attributes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dprc_open (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dprc_scan_container (struct fsl_mc_device*) ; 
 int dprc_setup_irq (struct fsl_mc_device*) ; 
 int fsl_create_mc_io (struct device*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  fsl_destroy_mc_io (int /*<<< orphan*/ *) ; 
 int fsl_mc_find_msi_domain (struct device*,struct irq_domain**) ; 
 int /*<<< orphan*/  is_fsl_mc_bus_dprc (struct fsl_mc_device*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 size_t resource_size (TYPE_2__*) ; 
 struct fsl_mc_bus* to_fsl_mc_bus (struct fsl_mc_device*) ; 

__attribute__((used)) static int dprc_probe(struct fsl_mc_device *mc_dev)
{
	int error;
	size_t region_size;
	struct device *parent_dev = mc_dev->dev.parent;
	struct fsl_mc_bus *mc_bus = to_fsl_mc_bus(mc_dev);
	bool mc_io_created = false;
	bool msi_domain_set = false;
	u16 major_ver, minor_ver;

	if (!is_fsl_mc_bus_dprc(mc_dev))
		return -EINVAL;

	if (dev_get_msi_domain(&mc_dev->dev))
		return -EINVAL;

	if (!mc_dev->mc_io) {
		/*
		 * This is a child DPRC:
		 */
		if (!dev_is_fsl_mc(parent_dev))
			return -EINVAL;

		if (mc_dev->obj_desc.region_count == 0)
			return -EINVAL;

		region_size = resource_size(mc_dev->regions);

		error = fsl_create_mc_io(&mc_dev->dev,
					 mc_dev->regions[0].start,
					 region_size,
					 NULL,
					 FSL_MC_IO_ATOMIC_CONTEXT_PORTAL,
					 &mc_dev->mc_io);
		if (error < 0)
			return error;

		mc_io_created = true;

		/*
		 * Inherit parent MSI domain:
		 */
		dev_set_msi_domain(&mc_dev->dev,
				   dev_get_msi_domain(parent_dev));
		msi_domain_set = true;
	} else {
		/*
		 * This is a root DPRC
		 */
		struct irq_domain *mc_msi_domain;

		if (dev_is_fsl_mc(parent_dev))
			return -EINVAL;

		error = fsl_mc_find_msi_domain(parent_dev,
					       &mc_msi_domain);
		if (error < 0) {
			dev_warn(&mc_dev->dev,
				 "WARNING: MC bus without interrupt support\n");
		} else {
			dev_set_msi_domain(&mc_dev->dev, mc_msi_domain);
			msi_domain_set = true;
		}
	}

	error = dprc_open(mc_dev->mc_io, 0, mc_dev->obj_desc.id,
			  &mc_dev->mc_handle);
	if (error < 0) {
		dev_err(&mc_dev->dev, "dprc_open() failed: %d\n", error);
		goto error_cleanup_msi_domain;
	}

	error = dprc_get_attributes(mc_dev->mc_io, 0, mc_dev->mc_handle,
				    &mc_bus->dprc_attr);
	if (error < 0) {
		dev_err(&mc_dev->dev, "dprc_get_attributes() failed: %d\n",
			error);
		goto error_cleanup_open;
	}

	error = dprc_get_api_version(mc_dev->mc_io, 0,
				     &major_ver,
				     &minor_ver);
	if (error < 0) {
		dev_err(&mc_dev->dev, "dprc_get_api_version() failed: %d\n",
			error);
		goto error_cleanup_open;
	}

	if (major_ver < DPRC_MIN_VER_MAJOR ||
	    (major_ver == DPRC_MIN_VER_MAJOR &&
	     minor_ver < DPRC_MIN_VER_MINOR)) {
		dev_err(&mc_dev->dev,
			"ERROR: DPRC version %d.%d not supported\n",
			major_ver, minor_ver);
		error = -ENOTSUPP;
		goto error_cleanup_open;
	}

	mutex_init(&mc_bus->scan_mutex);

	/*
	 * Discover MC objects in DPRC object:
	 */
	error = dprc_scan_container(mc_dev);
	if (error < 0)
		goto error_cleanup_open;

	/*
	 * Configure interrupt for the DPRC object associated with this MC bus:
	 */
	error = dprc_setup_irq(mc_dev);
	if (error < 0)
		goto error_cleanup_open;

	dev_info(&mc_dev->dev, "DPRC device bound to driver");
	return 0;

error_cleanup_open:
	(void)dprc_close(mc_dev->mc_io, 0, mc_dev->mc_handle);

error_cleanup_msi_domain:
	if (msi_domain_set)
		dev_set_msi_domain(&mc_dev->dev, NULL);

	if (mc_io_created) {
		fsl_destroy_mc_io(mc_dev->mc_io);
		mc_dev->mc_io = NULL;
	}

	return error;
}