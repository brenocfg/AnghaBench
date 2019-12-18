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
struct ntb_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ntb_mw_clear_trans (struct ntb_dev*,int,int) ; 
 int ntb_peer_highest_mw_idx (struct ntb_dev*,int) ; 
 int ntb_peer_port_count (struct ntb_dev*) ; 

void ntb_msi_clear_mws(struct ntb_dev *ntb)
{
	int peer;
	int peer_widx;

	for (peer = 0; peer < ntb_peer_port_count(ntb); peer++) {
		peer_widx = ntb_peer_highest_mw_idx(ntb, peer);
		if (peer_widx < 0)
			continue;

		ntb_mw_clear_trans(ntb, peer, peer_widx);
	}
}