#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int rx_status; } ;
union ep_buffer_info {TYPE_3__ v1i; } ;
struct TYPE_8__ {int /*<<< orphan*/  buffer_unshare_reserve_bit; int /*<<< orphan*/  share; } ;
struct fjes_hw {int max_epid; int my_epid; TYPE_4__ hw_info; TYPE_2__* ep_shm_info; } ;
typedef  enum ep_partner_status { ____Placeholder_ep_partner_status } ep_partner_status ;
struct TYPE_5__ {union ep_buffer_info* info; } ;
struct TYPE_6__ {TYPE_1__ rx; } ;

/* Variables and functions */
 int EBUSY ; 
 int FJES_COMMAND_EPSTOP_WAIT_TIMEOUT ; 
 int FJES_RX_STOP_REQ_DONE ; 
 int /*<<< orphan*/  clear_bit (int,int /*<<< orphan*/ *) ; 
 int fjes_hw_epid_is_shared (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 

int fjes_hw_wait_epstop(struct fjes_hw *hw)
{
	enum ep_partner_status status;
	union ep_buffer_info *info;
	int wait_time = 0;
	int epidx;

	while (hw->hw_info.buffer_unshare_reserve_bit &&
	       (wait_time < FJES_COMMAND_EPSTOP_WAIT_TIMEOUT * 1000)) {
		for (epidx = 0; epidx < hw->max_epid; epidx++) {
			if (epidx == hw->my_epid)
				continue;
			status = fjes_hw_epid_is_shared(hw->hw_info.share,
							epidx);
			info = hw->ep_shm_info[epidx].rx.info;
			if ((!status ||
			     (info->v1i.rx_status &
			      FJES_RX_STOP_REQ_DONE)) &&
			    test_bit(epidx,
				     &hw->hw_info.buffer_unshare_reserve_bit)) {
				clear_bit(epidx,
					  &hw->hw_info.buffer_unshare_reserve_bit);
			}
		}

		msleep(100);
		wait_time += 100;
	}

	for (epidx = 0; epidx < hw->max_epid; epidx++) {
		if (epidx == hw->my_epid)
			continue;
		if (test_bit(epidx, &hw->hw_info.buffer_unshare_reserve_bit))
			clear_bit(epidx,
				  &hw->hw_info.buffer_unshare_reserve_bit);
	}

	return (wait_time < FJES_COMMAND_EPSTOP_WAIT_TIMEOUT * 1000)
			? 0 : -EBUSY;
}