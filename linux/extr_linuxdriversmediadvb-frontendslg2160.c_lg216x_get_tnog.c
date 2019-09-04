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
struct lg216x_state {int dummy; } ;

/* Variables and functions */
 int lg216x_read_reg (struct lg216x_state*,int,int*) ; 
 scalar_t__ lg_fail (int) ; 

__attribute__((used)) static int lg216x_get_tnog(struct lg216x_state *state, u8 *tnog)
{
	u8 val;
	int ret;

	*tnog = 0xff; /* invalid value */

	ret = lg216x_read_reg(state, 0x0125, &val);
	if (lg_fail(ret))
		goto fail;

	*tnog = val & 0x1f;
fail:
	return ret;
}