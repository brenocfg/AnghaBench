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
struct vio_dev {int dummy; } ;
struct hvcs_struct {int p_unit_address; int /*<<< orphan*/  lock; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct hvcs_struct* from_vio_dev (struct vio_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int sprintf (char*,char*,int) ; 
 struct vio_dev* to_vio_dev (struct device*) ; 

__attribute__((used)) static ssize_t hvcs_partner_vtys_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct vio_dev *viod = to_vio_dev(dev);
	struct hvcs_struct *hvcsd = from_vio_dev(viod);
	unsigned long flags;
	int retval;

	spin_lock_irqsave(&hvcsd->lock, flags);
	retval = sprintf(buf, "%X\n", hvcsd->p_unit_address);
	spin_unlock_irqrestore(&hvcsd->lock, flags);
	return retval;
}