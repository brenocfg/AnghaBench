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
struct vchiq_arm_state {scalar_t__ resume_blocked; int /*<<< orphan*/  resume_blocker; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
unblock_resume(struct vchiq_arm_state *arm_state)
{
	complete_all(&arm_state->resume_blocker);
	arm_state->resume_blocked = 0;
}