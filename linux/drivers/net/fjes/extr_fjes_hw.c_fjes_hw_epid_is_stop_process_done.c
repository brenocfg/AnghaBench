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
struct fjes_hw {TYPE_4__* ep_shm_info; } ;
struct TYPE_7__ {TYPE_2__* info; } ;
struct TYPE_8__ {TYPE_3__ tx; } ;
struct TYPE_5__ {int rx_status; } ;
struct TYPE_6__ {TYPE_1__ v1i; } ;

/* Variables and functions */
 int FJES_RX_STOP_REQ_DONE ; 

__attribute__((used)) static bool fjes_hw_epid_is_stop_process_done(struct fjes_hw *hw, int src_epid)
{
	return (hw->ep_shm_info[src_epid].tx.info->v1i.rx_status &
			FJES_RX_STOP_REQ_DONE);
}