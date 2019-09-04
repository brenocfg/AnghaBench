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
struct update_flash_t {int /*<<< orphan*/  status; } ;
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FLASH_IMG_READY ; 
 int /*<<< orphan*/  FLASH_INVALID_IMG ; 
 int /*<<< orphan*/  FLASH_NO_OP ; 
 int /*<<< orphan*/  FLASH_UPDATE_CANCEL ; 
 int /*<<< orphan*/  FLASH_UPDATE_INIT ; 
 int /*<<< orphan*/  IMAGE_READY ; 
 TYPE_1__ image_data ; 
 int /*<<< orphan*/  image_data_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opal_flash_update (int /*<<< orphan*/ ) ; 
 struct update_flash_t update_flash_data ; 

__attribute__((used)) static ssize_t update_store(struct kobject *kobj,
			    struct kobj_attribute *attr,
			    const char *buf, size_t count)
{
	struct update_flash_t *const args_buf = &update_flash_data;
	int rc = count;

	mutex_lock(&image_data_mutex);

	switch (buf[0]) {
	case '0':
		if (args_buf->status == FLASH_IMG_READY)
			opal_flash_update(FLASH_UPDATE_CANCEL);
		args_buf->status = FLASH_NO_OP;
		break;
	case '1':
		/* Image is loaded? */
		if (image_data.status == IMAGE_READY)
			args_buf->status =
				opal_flash_update(FLASH_UPDATE_INIT);
		else
			args_buf->status = FLASH_INVALID_IMG;
		break;
	default:
		rc = -EINVAL;
	}

	mutex_unlock(&image_data_mutex);
	return rc;
}