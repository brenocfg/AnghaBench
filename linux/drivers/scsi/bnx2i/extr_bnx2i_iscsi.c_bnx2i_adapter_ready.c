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
struct bnx2i_hba {int /*<<< orphan*/  adapter_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAPTER_STATE_GOING_DOWN ; 
 int /*<<< orphan*/  ADAPTER_STATE_LINK_DOWN ; 
 int /*<<< orphan*/  ADAPTER_STATE_UP ; 
 int EPERM ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2i_adapter_ready(struct bnx2i_hba *hba)
{
	int retval = 0;

	if (!hba || !test_bit(ADAPTER_STATE_UP, &hba->adapter_state) ||
	    test_bit(ADAPTER_STATE_GOING_DOWN, &hba->adapter_state) ||
	    test_bit(ADAPTER_STATE_LINK_DOWN, &hba->adapter_state))
		retval = -EPERM;
	return retval;
}