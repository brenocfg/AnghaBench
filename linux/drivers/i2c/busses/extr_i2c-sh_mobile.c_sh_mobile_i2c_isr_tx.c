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
struct sh_mobile_i2c_data {int pos; TYPE_1__* msg; } ;
struct TYPE_2__ {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_TX ; 
 int /*<<< orphan*/  OP_TX_FIRST ; 
 int /*<<< orphan*/  OP_TX_STOP ; 
 int /*<<< orphan*/  i2c_op (struct sh_mobile_i2c_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sh_mobile_i2c_isr_tx(struct sh_mobile_i2c_data *pd)
{
	if (pd->pos == pd->msg->len) {
		i2c_op(pd, OP_TX_STOP);
		return 1;
	}

	if (pd->pos == -1)
		i2c_op(pd, OP_TX_FIRST);
	else
		i2c_op(pd, OP_TX);

	pd->pos++;
	return 0;
}