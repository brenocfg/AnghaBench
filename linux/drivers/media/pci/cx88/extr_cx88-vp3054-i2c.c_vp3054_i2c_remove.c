#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vp3054_i2c_state {int /*<<< orphan*/  adap; } ;
struct cx8802_dev {TYPE_1__* core; struct vp3054_i2c_state* vp3054; } ;
struct TYPE_2__ {scalar_t__ boardnr; } ;

/* Variables and functions */
 scalar_t__ CX88_BOARD_DNTV_LIVE_DVB_T_PRO ; 
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vp3054_i2c_state*) ; 

void vp3054_i2c_remove(struct cx8802_dev *dev)
{
	struct vp3054_i2c_state *vp3054_i2c = dev->vp3054;

	if (!vp3054_i2c ||
	    dev->core->boardnr != CX88_BOARD_DNTV_LIVE_DVB_T_PRO)
		return;

	i2c_del_adapter(&vp3054_i2c->adap);
	kfree(vp3054_i2c);
}