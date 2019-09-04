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
 int /*<<< orphan*/  IOPRIO_CLASS_BE ; 
 int /*<<< orphan*/  IOPRIO_NORM ; 
 unsigned short IOPRIO_PRIO_VALUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioprio_valid (unsigned short) ; 
 int min (unsigned short,unsigned short) ; 

int ioprio_best(unsigned short aprio, unsigned short bprio)
{
	if (!ioprio_valid(aprio))
		aprio = IOPRIO_PRIO_VALUE(IOPRIO_CLASS_BE, IOPRIO_NORM);
	if (!ioprio_valid(bprio))
		bprio = IOPRIO_PRIO_VALUE(IOPRIO_CLASS_BE, IOPRIO_NORM);

	return min(aprio, bprio);
}