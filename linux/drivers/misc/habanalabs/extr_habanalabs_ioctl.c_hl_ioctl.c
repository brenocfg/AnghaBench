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
struct hl_ioctl_desc {int dummy; } ;
struct hl_fpriv {struct hl_device* hdev; } ;
struct hl_device {int /*<<< orphan*/  dev; } ;
struct file {struct hl_fpriv* private_data; } ;

/* Variables and functions */
 long ENOTTY ; 
 unsigned int HL_COMMAND_END ; 
 unsigned int HL_COMMAND_START ; 
 unsigned int _IOC_NR (unsigned int) ; 
 long _hl_ioctl (struct file*,unsigned int,unsigned long,struct hl_ioctl_desc const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,unsigned int) ; 
 struct hl_ioctl_desc* hl_ioctls ; 
 int /*<<< orphan*/  task_pid_nr (int /*<<< orphan*/ ) ; 

long hl_ioctl(struct file *filep, unsigned int cmd, unsigned long arg)
{
	struct hl_fpriv *hpriv = filep->private_data;
	struct hl_device *hdev = hpriv->hdev;
	const struct hl_ioctl_desc *ioctl = NULL;
	unsigned int nr = _IOC_NR(cmd);

	if ((nr >= HL_COMMAND_START) && (nr < HL_COMMAND_END)) {
		ioctl = &hl_ioctls[nr];
	} else {
		dev_err(hdev->dev, "invalid ioctl: pid=%d, nr=0x%02x\n",
			task_pid_nr(current), nr);
		return -ENOTTY;
	}

	return _hl_ioctl(filep, cmd, arg, ioctl, hdev->dev);
}