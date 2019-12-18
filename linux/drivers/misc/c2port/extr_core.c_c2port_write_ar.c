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
typedef  int u8 ;
struct c2port_ops {int /*<<< orphan*/  (* c2d_dir ) (struct c2port_device*,int) ;int /*<<< orphan*/  (* c2d_set ) (struct c2port_device*,int) ;} ;
struct c2port_device {struct c2port_ops* ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  c2port_strobe_ck (struct c2port_device*) ; 
 int /*<<< orphan*/  stub1 (struct c2port_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct c2port_device*,int) ; 
 int /*<<< orphan*/  stub3 (struct c2port_device*,int) ; 
 int /*<<< orphan*/  stub4 (struct c2port_device*,int) ; 
 int /*<<< orphan*/  stub5 (struct c2port_device*,int) ; 

__attribute__((used)) static void c2port_write_ar(struct c2port_device *dev, u8 addr)
{
	struct c2port_ops *ops = dev->ops;
	int i;

	/* START field */
	c2port_strobe_ck(dev);

	/* INS field (11b, LSB first) */
	ops->c2d_dir(dev, 0);
	ops->c2d_set(dev, 1);
	c2port_strobe_ck(dev);
	ops->c2d_set(dev, 1);
	c2port_strobe_ck(dev);

	/* ADDRESS field */
	for (i = 0; i < 8; i++) {
		ops->c2d_set(dev, addr & 0x01);
		c2port_strobe_ck(dev);

		addr >>= 1;
	}

	/* STOP field */
	ops->c2d_dir(dev, 1);
	c2port_strobe_ck(dev);
}