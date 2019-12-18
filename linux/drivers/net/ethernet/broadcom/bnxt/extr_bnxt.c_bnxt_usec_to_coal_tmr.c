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
typedef  int u16 ;
struct bnxt_coal_cap {int timer_units; } ;
struct bnxt {struct bnxt_coal_cap coal_cap; } ;

/* Variables and functions */

__attribute__((used)) static u16 bnxt_usec_to_coal_tmr(struct bnxt *bp, u16 usec)
{
	struct bnxt_coal_cap *coal_cap = &bp->coal_cap;

	return usec * 1000 / coal_cap->timer_units;
}