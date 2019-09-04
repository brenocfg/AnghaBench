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
struct nios2_timer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALTERA_TIMER_CONTROL_REG ; 
 int /*<<< orphan*/  ALTERA_TIMER_CONTROL_START_MSK ; 
 int /*<<< orphan*/  timer_readw (struct nios2_timer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timer_writew (struct nios2_timer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nios2_timer_start(struct nios2_timer *timer)
{
	u16 ctrl;

	ctrl = timer_readw(timer, ALTERA_TIMER_CONTROL_REG);
	ctrl |= ALTERA_TIMER_CONTROL_START_MSK;
	timer_writew(timer, ctrl, ALTERA_TIMER_CONTROL_REG);
}