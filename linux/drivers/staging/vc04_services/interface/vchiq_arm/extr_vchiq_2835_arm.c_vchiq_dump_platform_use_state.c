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
struct vchiq_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vchiq_arm_log_level ; 
 int /*<<< orphan*/  vchiq_log_info (int /*<<< orphan*/ ,char*) ; 

void
vchiq_dump_platform_use_state(struct vchiq_state *state)
{
	vchiq_log_info(vchiq_arm_log_level, "Suspend timer not in use");
}