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
struct nios2_timer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALTERA_TIMER_SNAPH_REG ; 
 int /*<<< orphan*/  ALTERA_TIMER_SNAPL_REG ; 
 int timer_readw (struct nios2_timer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_writew (struct nios2_timer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long read_timersnapshot(struct nios2_timer *timer)
{
	unsigned long count;

	timer_writew(timer, 0, ALTERA_TIMER_SNAPL_REG);
	count = timer_readw(timer, ALTERA_TIMER_SNAPH_REG) << 16 |
		timer_readw(timer, ALTERA_TIMER_SNAPL_REG);

	return count;
}