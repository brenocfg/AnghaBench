#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  kobj; } ;
struct cxl_afu {TYPE_2__ dev; int /*<<< orphan*/  crs_len; } ;
struct TYPE_7__ {char* name; int /*<<< orphan*/  mode; } ;
struct TYPE_9__ {int /*<<< orphan*/  read; int /*<<< orphan*/  size; TYPE_1__ attr; } ;
struct afu_config_record {int cr; int class; int /*<<< orphan*/  kobj; TYPE_3__ config_attr; int /*<<< orphan*/  vendor; int /*<<< orphan*/  device; } ;
struct TYPE_10__ {int (* afu_cr_read16 ) (struct cxl_afu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int (* afu_cr_read32 ) (struct cxl_afu*,int,int /*<<< orphan*/ ,int*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 struct afu_config_record* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_ADD ; 
 int /*<<< orphan*/  PCI_CLASS_REVISION ; 
 int /*<<< orphan*/  PCI_DEVICE_ID ; 
 int /*<<< orphan*/  PCI_VENDOR_ID ; 
 int /*<<< orphan*/  S_IRUSR ; 
 int /*<<< orphan*/  afu_config_record_type ; 
 int /*<<< orphan*/  afu_read_config ; 
 TYPE_6__* cxl_ops ; 
 int /*<<< orphan*/  kfree (struct afu_config_record*) ; 
 int kobject_init_and_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct afu_config_record* kzalloc (int,int /*<<< orphan*/ ) ; 
 int stub1 (struct cxl_afu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub2 (struct cxl_afu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int stub3 (struct cxl_afu*,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sysfs_bin_attr_init (TYPE_3__*) ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  sysfs_remove_bin_file (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static struct afu_config_record *cxl_sysfs_afu_new_cr(struct cxl_afu *afu, int cr_idx)
{
	struct afu_config_record *cr;
	int rc;

	cr = kzalloc(sizeof(struct afu_config_record), GFP_KERNEL);
	if (!cr)
		return ERR_PTR(-ENOMEM);

	cr->cr = cr_idx;

	rc = cxl_ops->afu_cr_read16(afu, cr_idx, PCI_DEVICE_ID, &cr->device);
	if (rc)
		goto err;
	rc = cxl_ops->afu_cr_read16(afu, cr_idx, PCI_VENDOR_ID, &cr->vendor);
	if (rc)
		goto err;
	rc = cxl_ops->afu_cr_read32(afu, cr_idx, PCI_CLASS_REVISION, &cr->class);
	if (rc)
		goto err;
	cr->class >>= 8;

	/*
	 * Export raw AFU PCIe like config record. For now this is read only by
	 * root - we can expand that later to be readable by non-root and maybe
	 * even writable provided we have a good use-case. Once we support
	 * exposing AFUs through a virtual PHB they will get that for free from
	 * Linux' PCI infrastructure, but until then it's not clear that we
	 * need it for anything since the main use case is just identifying
	 * AFUs, which can be done via the vendor, device and class attributes.
	 */
	sysfs_bin_attr_init(&cr->config_attr);
	cr->config_attr.attr.name = "config";
	cr->config_attr.attr.mode = S_IRUSR;
	cr->config_attr.size = afu->crs_len;
	cr->config_attr.read = afu_read_config;

	rc = kobject_init_and_add(&cr->kobj, &afu_config_record_type,
				  &afu->dev.kobj, "cr%i", cr->cr);
	if (rc)
		goto err;

	rc = sysfs_create_bin_file(&cr->kobj, &cr->config_attr);
	if (rc)
		goto err1;

	rc = kobject_uevent(&cr->kobj, KOBJ_ADD);
	if (rc)
		goto err2;

	return cr;
err2:
	sysfs_remove_bin_file(&cr->kobj, &cr->config_attr);
err1:
	kobject_put(&cr->kobj);
	return ERR_PTR(rc);
err:
	kfree(cr);
	return ERR_PTR(rc);
}