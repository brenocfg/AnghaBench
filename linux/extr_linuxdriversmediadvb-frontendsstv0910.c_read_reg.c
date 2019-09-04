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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct stv {TYPE_1__* base; } ;
struct TYPE_2__ {int /*<<< orphan*/  adr; int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int i2c_read_regs16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int read_reg(struct stv *state, u16 reg, u8 *val)
{
	return i2c_read_regs16(state->base->i2c, state->base->adr,
			       reg, val, 1);
}