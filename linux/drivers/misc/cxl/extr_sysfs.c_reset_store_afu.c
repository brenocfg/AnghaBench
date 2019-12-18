#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
struct cxl_afu {int /*<<< orphan*/  contexts_lock; int /*<<< orphan*/  contexts_idr; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* afu_reset ) (struct cxl_afu*) ;} ;

/* Variables and functions */
 int EBUSY ; 
 TYPE_1__* cxl_ops ; 
 int /*<<< orphan*/  idr_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct cxl_afu*) ; 
 struct cxl_afu* to_cxl_afu (struct device*) ; 

__attribute__((used)) static ssize_t reset_store_afu(struct device *device,
			       struct device_attribute *attr,
			       const char *buf, size_t count)
{
	struct cxl_afu *afu = to_cxl_afu(device);
	int rc;

	/* Not safe to reset if it is currently in use */
	mutex_lock(&afu->contexts_lock);
	if (!idr_is_empty(&afu->contexts_idr)) {
		rc = -EBUSY;
		goto err;
	}

	if ((rc = cxl_ops->afu_reset(afu)))
		goto err;

	rc = count;
err:
	mutex_unlock(&afu->contexts_lock);
	return rc;
}