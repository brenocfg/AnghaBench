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

/* Variables and functions */
 size_t B ; 
 int /*<<< orphan*/  EGRET_TACK_NEGATED_DELAY ; 
 int TACK ; 
 int in_8 (int /*<<< orphan*/ *) ; 
 scalar_t__ mcu_is_egret ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * via ; 

__attribute__((used)) static inline void assert_TACK(void)
{
	if (mcu_is_egret) {
		udelay(EGRET_TACK_NEGATED_DELAY);
		out_8(&via[B], in_8(&via[B]) | TACK);
	} else
		out_8(&via[B], in_8(&via[B]) & ~TACK);
}