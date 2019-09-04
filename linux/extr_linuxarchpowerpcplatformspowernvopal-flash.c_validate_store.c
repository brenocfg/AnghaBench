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
struct validate_flash_t {scalar_t__ buf_size; int /*<<< orphan*/  status; int /*<<< orphan*/  buf; int /*<<< orphan*/  result; } ;
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {scalar_t__ status; scalar_t__ size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 size_t EINVAL ; 
 scalar_t__ IMAGE_READY ; 
 scalar_t__ VALIDATE_BUF_SIZE ; 
 int /*<<< orphan*/  VALIDATE_IMG_INCOMPLETE ; 
 int /*<<< orphan*/  VALIDATE_IMG_READY ; 
 int /*<<< orphan*/  VALIDATE_INVALID_IMG ; 
 TYPE_1__ image_data ; 
 int /*<<< orphan*/  image_data_mutex ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opal_flash_validate () ; 
 struct validate_flash_t validate_flash_data ; 

__attribute__((used)) static ssize_t validate_store(struct kobject *kobj,
			      struct kobj_attribute *attr,
			      const char *buf, size_t count)
{
	struct validate_flash_t *args_buf = &validate_flash_data;

	if (buf[0] != '1')
		return -EINVAL;

	mutex_lock(&image_data_mutex);

	if (image_data.status != IMAGE_READY ||
	    image_data.size < VALIDATE_BUF_SIZE) {
		args_buf->result = VALIDATE_INVALID_IMG;
		args_buf->status = VALIDATE_IMG_INCOMPLETE;
		goto out;
	}

	/* Copy first 4k bytes of candidate image */
	memcpy(args_buf->buf, image_data.data, VALIDATE_BUF_SIZE);

	args_buf->status = VALIDATE_IMG_READY;
	args_buf->buf_size = VALIDATE_BUF_SIZE;

	/* Validate candidate image */
	opal_flash_validate();

out:
	mutex_unlock(&image_data_mutex);
	return count;
}