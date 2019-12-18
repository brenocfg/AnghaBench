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
struct TYPE_4__ {int config_size; } ;
struct TYPE_3__ {int end; scalar_t__ start; int /*<<< orphan*/  name; } ;
struct nvdimm_drvdata {int ns_current; int ns_next; TYPE_2__ nsarea; int /*<<< orphan*/  kref; struct device* dev; TYPE_1__ dpa; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int ENOMEM ; 
 int ENOTTY ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_drvdata (struct device*,struct nvdimm_drvdata*) ; 
 int /*<<< orphan*/  get_device (struct device*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct nvdimm_drvdata* kzalloc (int,int /*<<< orphan*/ ) ; 
 int nd_label_data_init (struct nvdimm_drvdata*) ; 
 int nd_label_reserve_dpa (struct nvdimm_drvdata*) ; 
 int /*<<< orphan*/  nvdimm_bus_lock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_bus_unlock (struct device*) ; 
 int nvdimm_check_config_data (struct device*) ; 
 int /*<<< orphan*/  nvdimm_clear_locked (struct device*) ; 
 int nvdimm_init_nsarea (struct nvdimm_drvdata*) ; 
 int nvdimm_security_setup_events (struct device*) ; 
 int nvdimm_security_unlock (struct device*) ; 
 int /*<<< orphan*/  nvdimm_set_aliasing (struct device*) ; 
 int /*<<< orphan*/  nvdimm_set_locked (struct device*) ; 
 int /*<<< orphan*/  put_ndd (struct nvdimm_drvdata*) ; 

__attribute__((used)) static int nvdimm_probe(struct device *dev)
{
	struct nvdimm_drvdata *ndd;
	int rc;

	rc = nvdimm_security_setup_events(dev);
	if (rc < 0) {
		dev_err(dev, "security event setup failed: %d\n", rc);
		return rc;
	}

	rc = nvdimm_check_config_data(dev);
	if (rc) {
		/* not required for non-aliased nvdimm, ex. NVDIMM-N */
		if (rc == -ENOTTY)
			rc = 0;
		return rc;
	}

	/*
	 * The locked status bit reflects explicit status codes from the
	 * label reading commands, revalidate it each time the driver is
	 * activated and re-reads the label area.
	 */
	nvdimm_clear_locked(dev);

	ndd = kzalloc(sizeof(*ndd), GFP_KERNEL);
	if (!ndd)
		return -ENOMEM;

	dev_set_drvdata(dev, ndd);
	ndd->dpa.name = dev_name(dev);
	ndd->ns_current = -1;
	ndd->ns_next = -1;
	ndd->dpa.start = 0;
	ndd->dpa.end = -1;
	ndd->dev = dev;
	get_device(dev);
	kref_init(&ndd->kref);

	/*
	 * Attempt to unlock, if the DIMM supports security commands,
	 * otherwise the locked indication is determined by explicit
	 * status codes from the label reading commands.
	 */
	rc = nvdimm_security_unlock(dev);
	if (rc < 0)
		dev_dbg(dev, "failed to unlock dimm: %d\n", rc);


	/*
	 * EACCES failures reading the namespace label-area-properties
	 * are interpreted as the DIMM capacity being locked but the
	 * namespace labels themselves being accessible.
	 */
	rc = nvdimm_init_nsarea(ndd);
	if (rc == -EACCES) {
		/*
		 * See nvdimm_namespace_common_probe() where we fail to
		 * allow namespaces to probe while the DIMM is locked,
		 * but we do allow for namespace enumeration.
		 */
		nvdimm_set_locked(dev);
		rc = 0;
	}
	if (rc)
		goto err;

	/*
	 * EACCES failures reading the namespace label-data are
	 * interpreted as the label area being locked in addition to the
	 * DIMM capacity. We fail the dimm probe to prevent regions from
	 * attempting to parse the label area.
	 */
	rc = nd_label_data_init(ndd);
	if (rc == -EACCES)
		nvdimm_set_locked(dev);
	if (rc)
		goto err;

	dev_dbg(dev, "config data size: %d\n", ndd->nsarea.config_size);

	nvdimm_bus_lock(dev);
	if (ndd->ns_current >= 0) {
		rc = nd_label_reserve_dpa(ndd);
		if (rc == 0)
			nvdimm_set_aliasing(dev);
	}
	nvdimm_bus_unlock(dev);

	if (rc)
		goto err;

	return 0;

 err:
	put_ndd(ndd);
	return rc;
}