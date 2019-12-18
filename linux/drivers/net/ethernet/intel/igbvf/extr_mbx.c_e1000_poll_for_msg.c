#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ (* check_for_msg ) (struct e1000_hw*) ;} ;
struct e1000_mbx_info {int timeout; int /*<<< orphan*/  usec_delay; TYPE_1__ ops; } ;
struct e1000_hw {struct e1000_mbx_info mbx; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_ERR_MBX ; 
 int /*<<< orphan*/  E1000_SUCCESS ; 
 scalar_t__ stub1 (struct e1000_hw*) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s32 e1000_poll_for_msg(struct e1000_hw *hw)
{
	struct e1000_mbx_info *mbx = &hw->mbx;
	int countdown = mbx->timeout;

	if (!mbx->ops.check_for_msg)
		goto out;

	while (countdown && mbx->ops.check_for_msg(hw)) {
		countdown--;
		udelay(mbx->usec_delay);
	}

	/* if we failed, all future posted messages fail until reset */
	if (!countdown)
		mbx->timeout = 0;
out:
	return countdown ? E1000_SUCCESS : -E1000_ERR_MBX;
}