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
struct fjes_hw {int /*<<< orphan*/  txrx_stop_req_bit; } ;

/* Variables and functions */
 int test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool fjes_hw_epid_is_stop_requested(struct fjes_hw *hw, int src_epid)
{
	return test_bit(src_epid, &hw->txrx_stop_req_bit);
}