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
typedef  int /*<<< orphan*/  u16 ;
struct sh_eth_private {int /*<<< orphan*/ * reg_offset; } ;

/* Variables and functions */

__attribute__((used)) static u16 sh_eth_tsu_get_offset(struct sh_eth_private *mdp, int enum_index)
{
	return mdp->reg_offset[enum_index];
}