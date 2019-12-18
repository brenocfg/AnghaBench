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
struct ice_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICE_CTL_Q_ADMIN ; 
 int /*<<< orphan*/  ICE_CTL_Q_MAILBOX ; 
 int /*<<< orphan*/  ice_shutdown_ctrlq (struct ice_hw*,int /*<<< orphan*/ ) ; 

void ice_shutdown_all_ctrlq(struct ice_hw *hw)
{
	/* Shutdown FW admin queue */
	ice_shutdown_ctrlq(hw, ICE_CTL_Q_ADMIN);
	/* Shutdown PF-VF Mailbox */
	ice_shutdown_ctrlq(hw, ICE_CTL_Q_MAILBOX);
}