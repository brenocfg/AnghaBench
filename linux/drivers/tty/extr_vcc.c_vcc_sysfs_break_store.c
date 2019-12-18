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
struct vcc_port {int /*<<< orphan*/  lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  VCC_CTL_BREAK ; 
 struct vcc_port* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sscanf (char const*,char*,int*) ; 
 int /*<<< orphan*/  vcc_kick_tx (struct vcc_port*) ; 
 scalar_t__ vcc_send_ctl (struct vcc_port*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t vcc_sysfs_break_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct vcc_port *port;
	unsigned long flags;
	int rv = count;
	int brk;

	port = dev_get_drvdata(dev);
	if (!port)
		return -ENODEV;

	spin_lock_irqsave(&port->lock, flags);

	if (sscanf(buf, "%ud", &brk) != 1 || brk != 1)
		rv = -EINVAL;
	else if (vcc_send_ctl(port, VCC_CTL_BREAK) < 0)
		vcc_kick_tx(port);

	spin_unlock_irqrestore(&port->lock, flags);

	return rv;
}