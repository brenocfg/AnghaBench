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
struct c2port_ops {scalar_t__ (* c2d_get ) (struct c2port_device*) ;int /*<<< orphan*/  (* c2d_dir ) (struct c2port_device*,int) ;int /*<<< orphan*/  (* c2d_set ) (struct c2port_device*,int) ;} ;
struct c2port_device {struct c2port_ops* ops; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  c2port_strobe_ck (struct c2port_device*) ; 
 int /*<<< orphan*/  stub1 (struct c2port_device*,int) ; 
 int /*<<< orphan*/  stub2 (struct c2port_device*,int) ; 
 int /*<<< orphan*/  stub3 (struct c2port_device*,int) ; 
 int /*<<< orphan*/  stub4 (struct c2port_device*,int) ; 
 int /*<<< orphan*/  stub5 (struct c2port_device*,int) ; 
 int /*<<< orphan*/  stub6 (struct c2port_device*,int) ; 
 int /*<<< orphan*/  stub7 (struct c2port_device*,int) ; 
 scalar_t__ stub8 (struct c2port_device*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int c2port_write_dr(struct c2port_device *dev, u8 data)
{
	struct c2port_ops *ops = dev->ops;
	int timeout, i;

	/* START field */
	c2port_strobe_ck(dev);

	/* INS field (01b, LSB first) */
	ops->c2d_dir(dev, 0);
	ops->c2d_set(dev, 1);
	c2port_strobe_ck(dev);
	ops->c2d_set(dev, 0);
	c2port_strobe_ck(dev);

	/* LENGTH field (00b, LSB first -> 1 byte) */
	ops->c2d_set(dev, 0);
	c2port_strobe_ck(dev);
	ops->c2d_set(dev, 0);
	c2port_strobe_ck(dev);

	/* DATA field */
	for (i = 0; i < 8; i++) {
		ops->c2d_set(dev, data & 0x01);
		c2port_strobe_ck(dev);

		data >>= 1;
	}

	/* WAIT field */
	ops->c2d_dir(dev, 1);
	timeout = 20;
	do {
		c2port_strobe_ck(dev);
		if (ops->c2d_get(dev))
			break;

		udelay(1);
	} while (--timeout > 0);
	if (timeout == 0)
		return -EIO;

	/* STOP field */
	c2port_strobe_ck(dev);

	return 0;
}