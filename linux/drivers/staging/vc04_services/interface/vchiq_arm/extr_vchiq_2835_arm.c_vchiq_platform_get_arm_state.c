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
struct vchiq_state {scalar_t__ platform_state; } ;
struct vchiq_arm_state {int dummy; } ;
struct vchiq_2835_state {struct vchiq_arm_state arm_state; int /*<<< orphan*/  inited; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

struct vchiq_arm_state*
vchiq_platform_get_arm_state(struct vchiq_state *state)
{
	struct vchiq_2835_state *platform_state;

	platform_state   = (struct vchiq_2835_state *)state->platform_state;

	WARN_ON_ONCE(!platform_state->inited);

	return &platform_state->arm_state;
}