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
struct mxl301rf_state {int dummy; } ;

/* Variables and functions */
 int raw_write (struct mxl301rf_state*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int reg_write(struct mxl301rf_state *state, u8 reg, u8 val)
{
	u8 buf[2] = { reg, val };

	return raw_write(state, buf, 2);
}