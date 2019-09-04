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
struct kobject {int dummy; } ;
struct file {int dummy; } ;
struct bin_attribute {int dummy; } ;
typedef  int ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_4__ {scalar_t__ data; scalar_t__ status; scalar_t__ size; } ;
struct TYPE_3__ {scalar_t__ status; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 scalar_t__ FLASH_IMG_READY ; 
 int /*<<< orphan*/  FLASH_UPDATE_CANCEL ; 
 scalar_t__ IMAGE_LOADING ; 
 scalar_t__ IMAGE_READY ; 
 int alloc_image_buf (char*,size_t) ; 
 int /*<<< orphan*/  free_image_buf () ; 
 TYPE_2__ image_data ; 
 int /*<<< orphan*/  image_data_mutex ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void*,size_t) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opal_flash_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 TYPE_1__ update_flash_data ; 

__attribute__((used)) static ssize_t image_data_write(struct file *filp, struct kobject *kobj,
				struct bin_attribute *bin_attr,
				char *buffer, loff_t pos, size_t count)
{
	int rc;

	mutex_lock(&image_data_mutex);

	/* New image ? */
	if (pos == 0) {
		/* Free memory, if already allocated */
		if (image_data.data)
			free_image_buf();

		/* Cancel outstanding image update request */
		if (update_flash_data.status == FLASH_IMG_READY)
			opal_flash_update(FLASH_UPDATE_CANCEL);

		/* Allocate memory */
		rc = alloc_image_buf(buffer, count);
		if (rc)
			goto out;
	}

	if (image_data.status != IMAGE_LOADING) {
		rc = -ENOMEM;
		goto out;
	}

	if ((pos + count) > image_data.size) {
		rc = -EINVAL;
		goto out;
	}

	memcpy(image_data.data + pos, (void *)buffer, count);
	rc = count;

	/* Set image status */
	if ((pos + count) == image_data.size) {
		pr_debug("FLASH: Candidate image loaded....\n");
		image_data.status = IMAGE_READY;
	}

out:
	mutex_unlock(&image_data_mutex);
	return rc;
}