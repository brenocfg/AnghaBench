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
struct c2port_ops {int /*<<< orphan*/  (* c2ck_set ) (struct c2port_device*,int) ;} ;
struct c2port_device {struct c2port_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  stub1 (struct c2port_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct c2port_device*,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void c2port_reset(struct c2port_device *dev)
{
	struct c2port_ops *ops = dev->ops;

	/* To reset the device we have to keep clock line low for at least
	 * 20us.
	 */
	local_irq_disable();
	ops->c2ck_set(dev, 0);
	udelay(25);
	ops->c2ck_set(dev, 1);
	local_irq_enable();

	udelay(1);
}