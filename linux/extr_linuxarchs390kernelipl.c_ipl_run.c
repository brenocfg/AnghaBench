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
struct shutdown_trigger {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __ipl_run ; 
 int /*<<< orphan*/  smp_call_ipl_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipl_run(struct shutdown_trigger *trigger)
{
	smp_call_ipl_cpu(__ipl_run, NULL);
}