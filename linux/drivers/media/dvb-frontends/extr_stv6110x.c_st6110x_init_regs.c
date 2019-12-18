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
struct stv6110x_state {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 

__attribute__((used)) static void st6110x_init_regs(struct stv6110x_state *stv6110x)
{
	u8 default_regs[] = {0x07, 0x11, 0xdc, 0x85, 0x17, 0x01, 0xe6, 0x1e};

	memcpy(stv6110x->regs, default_regs, 8);
}