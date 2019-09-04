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
struct mce {int cs; int /*<<< orphan*/  ip; int /*<<< orphan*/  mcgstatus; } ;

/* Variables and functions */
 int IN_KERNEL ; 
 int IN_KERNEL_RECOV ; 
 int IN_USER ; 
 scalar_t__ ex_has_fault_handler (int /*<<< orphan*/ ) ; 
 scalar_t__ mc_recoverable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int error_context(struct mce *m)
{
	if ((m->cs & 3) == 3)
		return IN_USER;
	if (mc_recoverable(m->mcgstatus) && ex_has_fault_handler(m->ip))
		return IN_KERNEL_RECOV;
	return IN_KERNEL;
}