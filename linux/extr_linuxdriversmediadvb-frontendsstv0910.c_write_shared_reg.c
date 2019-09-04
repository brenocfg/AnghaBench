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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct stv {TYPE_1__* base; } ;
struct TYPE_2__ {int /*<<< orphan*/  reg_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int read_reg (struct stv*,int /*<<< orphan*/ ,int*) ; 
 int write_reg (struct stv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int write_shared_reg(struct stv *state, u16 reg, u8 mask, u8 val)
{
	int status;
	u8 tmp;

	mutex_lock(&state->base->reg_lock);
	status = read_reg(state, reg, &tmp);
	if (!status)
		status = write_reg(state, reg, (tmp & ~mask) | (val & mask));
	mutex_unlock(&state->base->reg_lock);
	return status;
}