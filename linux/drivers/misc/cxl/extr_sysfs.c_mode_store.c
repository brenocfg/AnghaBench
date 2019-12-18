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
struct cxl_afu {int current_mode; int /*<<< orphan*/  contexts_lock; scalar_t__ num_procs; int /*<<< orphan*/  contexts_idr; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int (* afu_deactivate_mode ) (struct cxl_afu*,int) ;int (* afu_activate_mode ) (struct cxl_afu*,int) ;} ;

/* Variables and functions */
 int CXL_MODE_DEDICATED ; 
 int CXL_MODE_DIRECTED ; 
 int EBUSY ; 
 int EINVAL ; 
 TYPE_1__* cxl_ops ; 
 int /*<<< orphan*/  idr_is_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 
 int stub1 (struct cxl_afu*,int) ; 
 int stub2 (struct cxl_afu*,int) ; 
 struct cxl_afu* to_cxl_afu (struct device*) ; 

__attribute__((used)) static ssize_t mode_store(struct device *device, struct device_attribute *attr,
			  const char *buf, size_t count)
{
	struct cxl_afu *afu = to_cxl_afu(device);
	int old_mode, mode = -1;
	int rc = -EBUSY;

	/* can't change this if we have a user */
	mutex_lock(&afu->contexts_lock);
	if (!idr_is_empty(&afu->contexts_idr))
		goto err;

	if (!strncmp(buf, "dedicated_process", 17))
		mode = CXL_MODE_DEDICATED;
	if (!strncmp(buf, "afu_directed", 12))
		mode = CXL_MODE_DIRECTED;
	if (!strncmp(buf, "none", 4))
		mode = 0;

	if (mode == -1) {
		rc = -EINVAL;
		goto err;
	}

	/*
	 * afu_deactivate_mode needs to be done outside the lock, prevent
	 * other contexts coming in before we are ready:
	 */
	old_mode = afu->current_mode;
	afu->current_mode = 0;
	afu->num_procs = 0;

	mutex_unlock(&afu->contexts_lock);

	if ((rc = cxl_ops->afu_deactivate_mode(afu, old_mode)))
		return rc;
	if ((rc = cxl_ops->afu_activate_mode(afu, mode)))
		return rc;

	return count;
err:
	mutex_unlock(&afu->contexts_lock);
	return rc;
}