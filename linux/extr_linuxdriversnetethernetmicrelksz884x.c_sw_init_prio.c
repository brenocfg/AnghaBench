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
struct ksz_switch {int* p_802_1p; TYPE_1__* port_cfg; scalar_t__* diffserv; } ;
struct ksz_hw {struct ksz_switch* ksz_switch; } ;
struct TYPE_2__ {scalar_t__ port_prio; } ;

/* Variables and functions */
 int DIFFSERV_ENTRIES ; 
 int TOTAL_PORT_NUM ; 
 int /*<<< orphan*/  sw_cfg_port_based (struct ksz_hw*,int,scalar_t__) ; 
 int /*<<< orphan*/  sw_cfg_replace_null_vid (struct ksz_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_cfg_replace_vid (struct ksz_hw*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sw_dis_802_1p (struct ksz_hw*,int) ; 
 int /*<<< orphan*/  sw_dis_diffserv (struct ksz_hw*,int) ; 
 int /*<<< orphan*/  sw_dis_multi_queue (struct ksz_hw*,int) ; 

__attribute__((used)) static void sw_init_prio(struct ksz_hw *hw)
{
	int port;
	int tos;
	struct ksz_switch *sw = hw->ksz_switch;

	/*
	 * Init all the 802.1p tag priority value to be assigned to different
	 * priority queue.
	 */
	sw->p_802_1p[0] = 0;
	sw->p_802_1p[1] = 0;
	sw->p_802_1p[2] = 1;
	sw->p_802_1p[3] = 1;
	sw->p_802_1p[4] = 2;
	sw->p_802_1p[5] = 2;
	sw->p_802_1p[6] = 3;
	sw->p_802_1p[7] = 3;

	/*
	 * Init all the DiffServ priority value to be assigned to priority
	 * queue 0.
	 */
	for (tos = 0; tos < DIFFSERV_ENTRIES; tos++)
		sw->diffserv[tos] = 0;

	/* All QoS functions disabled. */
	for (port = 0; port < TOTAL_PORT_NUM; port++) {
		sw_dis_multi_queue(hw, port);
		sw_dis_diffserv(hw, port);
		sw_dis_802_1p(hw, port);
		sw_cfg_replace_vid(hw, port, 0);

		sw->port_cfg[port].port_prio = 0;
		sw_cfg_port_based(hw, port, sw->port_cfg[port].port_prio);
	}
	sw_cfg_replace_null_vid(hw, 0);
}