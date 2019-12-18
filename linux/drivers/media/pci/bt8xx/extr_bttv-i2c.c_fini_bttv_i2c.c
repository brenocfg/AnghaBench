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
struct TYPE_2__ {int /*<<< orphan*/  i2c_adap; } ;
struct bttv {scalar_t__ i2c_rc; TYPE_1__ c; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_del_adapter (int /*<<< orphan*/ *) ; 

int fini_bttv_i2c(struct bttv *btv)
{
	if (btv->i2c_rc == 0)
		i2c_del_adapter(&btv->c.i2c_adap);

	return 0;
}