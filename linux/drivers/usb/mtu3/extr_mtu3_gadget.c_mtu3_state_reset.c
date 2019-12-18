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
struct mtu3 {int delayed_status; int test_mode; scalar_t__ u2_enable; scalar_t__ u1_enable; scalar_t__ may_wakeup; int /*<<< orphan*/  ep0_state; scalar_t__ address; } ;

/* Variables and functions */
 int /*<<< orphan*/  MU3D_EP0_STATE_SETUP ; 

__attribute__((used)) static void mtu3_state_reset(struct mtu3 *mtu)
{
	mtu->address = 0;
	mtu->ep0_state = MU3D_EP0_STATE_SETUP;
	mtu->may_wakeup = 0;
	mtu->u1_enable = 0;
	mtu->u2_enable = 0;
	mtu->delayed_status = false;
	mtu->test_mode = false;
}