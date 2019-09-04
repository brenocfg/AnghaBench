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
struct file {int dummy; } ;

/* Variables and functions */
#define  CMD_WRITE_BASE64K_ENABLE 130 
#define  CMD_WRITE_DISABLE 129 
#define  CMD_WRITE_ENABLE 128 
 long EINVAL ; 
 int /*<<< orphan*/  flash_mutex ; 
 int gbWriteBase64Enable ; 
 int gbWriteEnable ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static long flash_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
	mutex_lock(&flash_mutex);
	switch (cmd) {
	case CMD_WRITE_DISABLE:
		gbWriteBase64Enable = 0;
		gbWriteEnable = 0;
		break;

	case CMD_WRITE_ENABLE:
		gbWriteEnable = 1;
		break;

	case CMD_WRITE_BASE64K_ENABLE:
		gbWriteBase64Enable = 1;
		break;

	default:
		gbWriteBase64Enable = 0;
		gbWriteEnable = 0;
		mutex_unlock(&flash_mutex);
		return -EINVAL;
	}
	mutex_unlock(&flash_mutex);
	return 0;
}