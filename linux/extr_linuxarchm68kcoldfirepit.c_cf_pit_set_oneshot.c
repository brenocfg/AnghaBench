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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCFPIT_PCSR ; 
 int MCFPIT_PCSR_CLK64 ; 
 int MCFPIT_PCSR_DISABLE ; 
 int MCFPIT_PCSR_EN ; 
 int MCFPIT_PCSR_OVW ; 
 int MCFPIT_PCSR_PIE ; 
 int /*<<< orphan*/  TA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cf_pit_set_oneshot(struct clock_event_device *evt)
{
	__raw_writew(MCFPIT_PCSR_DISABLE, TA(MCFPIT_PCSR));
	__raw_writew(MCFPIT_PCSR_EN | MCFPIT_PCSR_PIE |
		     MCFPIT_PCSR_OVW | MCFPIT_PCSR_CLK64, TA(MCFPIT_PCSR));
	return 0;
}