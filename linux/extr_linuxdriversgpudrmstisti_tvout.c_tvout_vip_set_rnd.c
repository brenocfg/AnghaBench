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
typedef  int u32 ;
struct sti_tvout {int dummy; } ;

/* Variables and functions */
 int TVO_VIP_RND_MASK ; 
 int TVO_VIP_RND_SHIFT ; 
 int tvout_read (struct sti_tvout*,int) ; 
 int /*<<< orphan*/  tvout_write (struct sti_tvout*,int,int) ; 

__attribute__((used)) static void tvout_vip_set_rnd(struct sti_tvout *tvout, int reg, u32 rnd)
{
	u32 val = tvout_read(tvout, reg);

	val &= ~(TVO_VIP_RND_MASK << TVO_VIP_RND_SHIFT);
	val |= rnd << TVO_VIP_RND_SHIFT;
	tvout_write(tvout, val, reg);
}