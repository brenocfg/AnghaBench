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
 int /*<<< orphan*/  MCFPIT_PCSR_DISABLE ; 
 int /*<<< orphan*/  TA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cf_pit_shutdown(struct clock_event_device *evt)
{
	__raw_writew(MCFPIT_PCSR_DISABLE, TA(MCFPIT_PCSR));
	return 0;
}