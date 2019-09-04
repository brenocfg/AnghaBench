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
struct rk_timer {int /*<<< orphan*/  ctrl; } ;

/* Variables and functions */
 int TIMER_ENABLE ; 
 int /*<<< orphan*/  writel_relaxed (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rk_timer_enable(struct rk_timer *timer, u32 flags)
{
	writel_relaxed(TIMER_ENABLE | flags, timer->ctrl);
}