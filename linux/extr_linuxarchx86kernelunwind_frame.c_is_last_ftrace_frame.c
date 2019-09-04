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
struct unwind_state {unsigned long* bp; } ;

/* Variables and functions */
 unsigned long* last_frame (struct unwind_state*) ; 

__attribute__((used)) static bool is_last_ftrace_frame(struct unwind_state *state)
{
	unsigned long *last_bp = last_frame(state);
	unsigned long *last_ftrace_bp = last_bp - 3;

	/*
	 * When unwinding from an ftrace handler of a function called by entry
	 * code, the stack layout of the last frame is:
	 *
	 *   bp
	 *   parent ret addr
	 *   bp
	 *   function ret addr
	 *   parent ret addr
	 *   pt_regs
	 *   -----------------
	 */
	return (state->bp == last_ftrace_bp &&
		*state->bp == *(state->bp + 2) &&
		*(state->bp + 1) == *(state->bp + 4));
}