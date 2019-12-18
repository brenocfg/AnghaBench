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
typedef  int /*<<< orphan*/  u32 ;
struct mei_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  H_D0I3C_I3 ; 
 int /*<<< orphan*/  H_D0I3C_IR ; 
 int /*<<< orphan*/  mei_me_d0i3c_read (struct mei_device*) ; 
 int /*<<< orphan*/  mei_me_d0i3c_write (struct mei_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 mei_me_d0i3_unset(struct mei_device *dev)
{
	u32 reg = mei_me_d0i3c_read(dev);

	reg &= ~H_D0I3C_I3;
	reg |= H_D0I3C_IR;
	mei_me_d0i3c_write(dev, reg);
	/* read it to ensure HW consistency */
	reg = mei_me_d0i3c_read(dev);
	return reg;
}