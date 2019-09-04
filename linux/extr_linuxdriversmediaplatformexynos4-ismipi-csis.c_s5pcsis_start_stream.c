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
struct csis_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  s5pcsis_enable_interrupts (struct csis_state*,int) ; 
 int /*<<< orphan*/  s5pcsis_reset (struct csis_state*) ; 
 int /*<<< orphan*/  s5pcsis_set_params (struct csis_state*) ; 
 int /*<<< orphan*/  s5pcsis_system_enable (struct csis_state*,int) ; 

__attribute__((used)) static void s5pcsis_start_stream(struct csis_state *state)
{
	s5pcsis_reset(state);
	s5pcsis_set_params(state);
	s5pcsis_system_enable(state, true);
	s5pcsis_enable_interrupts(state, true);
}