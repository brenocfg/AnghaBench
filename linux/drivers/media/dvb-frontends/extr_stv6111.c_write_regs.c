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
struct stv {int /*<<< orphan*/  adr; int /*<<< orphan*/  i2c; int /*<<< orphan*/ * reg; } ;

/* Variables and functions */
 int i2c_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int write_regs(struct stv *state, int reg, int len)
{
	u8 d[12];

	memcpy(&d[1], &state->reg[reg], len);
	d[0] = reg;
	return i2c_write(state->i2c, state->adr, d, len + 1);
}