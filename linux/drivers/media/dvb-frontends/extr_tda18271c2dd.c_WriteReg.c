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
typedef  int /*<<< orphan*/  u8 ;
struct tda_state {int /*<<< orphan*/  adr; int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int i2c_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int WriteReg(struct tda_state *state, u8 SubAddr, u8 Reg)
{
	u8 msg[2] = {SubAddr, Reg};

	return i2c_write(state->i2c, state->adr, msg, 2);
}