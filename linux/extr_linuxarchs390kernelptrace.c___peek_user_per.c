#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long address; scalar_t__ paid; scalar_t__ cause; } ;
struct TYPE_4__ {unsigned long control; unsigned long start; unsigned long end; } ;
struct TYPE_6__ {TYPE_2__ per_event; TYPE_1__ per_user; } ;
struct task_struct {TYPE_3__ thread; } ;
struct per_struct_kernel {int /*<<< orphan*/  access_id; int /*<<< orphan*/  address; int /*<<< orphan*/  perc_atmid; int /*<<< orphan*/  ending_addr; int /*<<< orphan*/  starting_addr; int /*<<< orphan*/  bits; int /*<<< orphan*/  cr11; int /*<<< orphan*/  cr10; int /*<<< orphan*/  cr9; } ;
typedef  scalar_t__ addr_t ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 unsigned long PER_EVENT_IFETCH ; 
 int /*<<< orphan*/  TIF_SINGLE_STEP ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned long __peek_user_per(struct task_struct *child,
					    addr_t addr)
{
	struct per_struct_kernel *dummy = NULL;

	if (addr == (addr_t) &dummy->cr9)
		/* Control bits of the active per set. */
		return test_thread_flag(TIF_SINGLE_STEP) ?
			PER_EVENT_IFETCH : child->thread.per_user.control;
	else if (addr == (addr_t) &dummy->cr10)
		/* Start address of the active per set. */
		return test_thread_flag(TIF_SINGLE_STEP) ?
			0 : child->thread.per_user.start;
	else if (addr == (addr_t) &dummy->cr11)
		/* End address of the active per set. */
		return test_thread_flag(TIF_SINGLE_STEP) ?
			-1UL : child->thread.per_user.end;
	else if (addr == (addr_t) &dummy->bits)
		/* Single-step bit. */
		return test_thread_flag(TIF_SINGLE_STEP) ?
			(1UL << (BITS_PER_LONG - 1)) : 0;
	else if (addr == (addr_t) &dummy->starting_addr)
		/* Start address of the user specified per set. */
		return child->thread.per_user.start;
	else if (addr == (addr_t) &dummy->ending_addr)
		/* End address of the user specified per set. */
		return child->thread.per_user.end;
	else if (addr == (addr_t) &dummy->perc_atmid)
		/* PER code, ATMID and AI of the last PER trap */
		return (unsigned long)
			child->thread.per_event.cause << (BITS_PER_LONG - 16);
	else if (addr == (addr_t) &dummy->address)
		/* Address of the last PER trap */
		return child->thread.per_event.address;
	else if (addr == (addr_t) &dummy->access_id)
		/* Access id of the last PER trap */
		return (unsigned long)
			child->thread.per_event.paid << (BITS_PER_LONG - 8);
	return 0;
}