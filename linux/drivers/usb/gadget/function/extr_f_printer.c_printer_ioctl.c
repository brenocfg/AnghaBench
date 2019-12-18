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
typedef  scalar_t__ u8 ;
struct printer_dev {int /*<<< orphan*/  lock; scalar_t__ printer_status; } ;
struct file {struct printer_dev* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (struct printer_dev*,char*,unsigned int,...) ; 
 int ENOTTY ; 
#define  GADGET_GET_PRINTER_STATUS 129 
#define  GADGET_SET_PRINTER_STATUS 128 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static long
printer_ioctl(struct file *fd, unsigned int code, unsigned long arg)
{
	struct printer_dev	*dev = fd->private_data;
	unsigned long		flags;
	int			status = 0;

	DBG(dev, "printer_ioctl: cmd=0x%4.4x, arg=%lu\n", code, arg);

	/* handle ioctls */

	spin_lock_irqsave(&dev->lock, flags);

	switch (code) {
	case GADGET_GET_PRINTER_STATUS:
		status = (int)dev->printer_status;
		break;
	case GADGET_SET_PRINTER_STATUS:
		dev->printer_status = (u8)arg;
		break;
	default:
		/* could not handle ioctl */
		DBG(dev, "printer_ioctl: ERROR cmd=0x%4.4xis not supported\n",
				code);
		status = -ENOTTY;
	}

	spin_unlock_irqrestore(&dev->lock, flags);

	return status;
}