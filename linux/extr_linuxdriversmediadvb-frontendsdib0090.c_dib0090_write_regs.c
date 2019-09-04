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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct dib0090_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dib0090_write_reg (struct dib0090_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dib0090_write_regs(struct dib0090_state *state, u8 r, const u16 * b, u8 c)
{
	do {
		dib0090_write_reg(state, r++, *b++);
	} while (--c);
}