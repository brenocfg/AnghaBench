#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct validate_flash_t {scalar_t__ status; int result; int buf_size; int /*<<< orphan*/  buf; } ;
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int FLASH_NO_OP ; 
 int VALIDATE_BUF_SIZE ; 
 scalar_t__ VALIDATE_CUR_UNKNOWN ; 
 scalar_t__ VALIDATE_TMP_UPDATE ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int sprintf (char*,char*,int) ; 
 struct validate_flash_t validate_flash_data ; 

__attribute__((used)) static ssize_t validate_show(struct kobject *kobj,
			     struct kobj_attribute *attr, char *buf)
{
	struct validate_flash_t *args_buf = &validate_flash_data;
	int len;

	/* Candidate image is not validated */
	if (args_buf->status < VALIDATE_TMP_UPDATE) {
		len = sprintf(buf, "%d\n", args_buf->status);
		goto out;
	}

	/* Result token */
	len = sprintf(buf, "%d\n", args_buf->result);

	/* Current and candidate image version details */
	if ((args_buf->result != VALIDATE_TMP_UPDATE) &&
	    (args_buf->result < VALIDATE_CUR_UNKNOWN))
		goto out;

	if (args_buf->buf_size > (VALIDATE_BUF_SIZE - len)) {
		memcpy(buf + len, args_buf->buf, VALIDATE_BUF_SIZE - len);
		len = VALIDATE_BUF_SIZE;
	} else {
		memcpy(buf + len, args_buf->buf, args_buf->buf_size);
		len += args_buf->buf_size;
	}
out:
	/* Set status to default */
	args_buf->status = FLASH_NO_OP;
	return len;
}