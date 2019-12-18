#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct device_attribute {TYPE_1__ attr; } ;
struct TYPE_6__ {char* name; int /*<<< orphan*/  mode; } ;
struct TYPE_7__ {int /*<<< orphan*/  read; scalar_t__ size; TYPE_2__ attr; } ;
struct cxl_afu {int crs_num; int /*<<< orphan*/  dev; scalar_t__ eb_len; int /*<<< orphan*/  crs; TYPE_3__ attr_eb; } ;
struct afu_config_record {int /*<<< orphan*/  list; } ;
struct TYPE_8__ {scalar_t__ (* support_attributes ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int ARRAY_SIZE (struct device_attribute*) ; 
 int /*<<< orphan*/  CXL_AFU_ATTRS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (struct afu_config_record*) ; 
 int PTR_ERR (struct afu_config_record*) ; 
 int /*<<< orphan*/  S_IRUGO ; 
 struct device_attribute* afu_attrs ; 
 int /*<<< orphan*/  afu_eb_read ; 
 TYPE_4__* cxl_ops ; 
 struct afu_config_record* cxl_sysfs_afu_new_cr (struct cxl_afu*,int) ; 
 int /*<<< orphan*/  cxl_sysfs_afu_remove (struct cxl_afu*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int device_create_bin_file (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int device_create_file (int /*<<< orphan*/ *,struct device_attribute*) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,struct device_attribute*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_2__*) ; 

int cxl_sysfs_afu_add(struct cxl_afu *afu)
{
	struct device_attribute *dev_attr;
	struct afu_config_record *cr;
	int i, rc;

	INIT_LIST_HEAD(&afu->crs);

	for (i = 0; i < ARRAY_SIZE(afu_attrs); i++) {
		dev_attr = &afu_attrs[i];
		if (cxl_ops->support_attributes(dev_attr->attr.name,
						CXL_AFU_ATTRS)) {
			if ((rc = device_create_file(&afu->dev, &afu_attrs[i])))
				goto err;
		}
	}

	/* conditionally create the add the binary file for error info buffer */
	if (afu->eb_len) {
		sysfs_attr_init(&afu->attr_eb.attr);

		afu->attr_eb.attr.name = "afu_err_buff";
		afu->attr_eb.attr.mode = S_IRUGO;
		afu->attr_eb.size = afu->eb_len;
		afu->attr_eb.read = afu_eb_read;

		rc = device_create_bin_file(&afu->dev, &afu->attr_eb);
		if (rc) {
			dev_err(&afu->dev,
				"Unable to create eb attr for the afu. Err(%d)\n",
				rc);
			goto err;
		}
	}

	for (i = 0; i < afu->crs_num; i++) {
		cr = cxl_sysfs_afu_new_cr(afu, i);
		if (IS_ERR(cr)) {
			rc = PTR_ERR(cr);
			goto err1;
		}
		list_add(&cr->list, &afu->crs);
	}

	return 0;

err1:
	cxl_sysfs_afu_remove(afu);
	return rc;
err:
	/* reset the eb_len as we havent created the bin attr */
	afu->eb_len = 0;

	for (i--; i >= 0; i--) {
		dev_attr = &afu_attrs[i];
		if (cxl_ops->support_attributes(dev_attr->attr.name,
						CXL_AFU_ATTRS))
		device_remove_file(&afu->dev, &afu_attrs[i]);
	}
	return rc;
}