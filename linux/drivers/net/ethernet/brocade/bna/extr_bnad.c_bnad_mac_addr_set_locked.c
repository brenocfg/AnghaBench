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
typedef  int /*<<< orphan*/  u8 ;
struct bnad {TYPE_1__* rx_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  rx; } ;

/* Variables and functions */
 int BNA_CB_SUCCESS ; 
 int EADDRNOTAVAIL ; 
 int bna_rx_ucast_set (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  is_valid_ether_addr (int /*<<< orphan*/  const*) ; 

int
bnad_mac_addr_set_locked(struct bnad *bnad, const u8 *mac_addr)
{
	int ret;

	if (!is_valid_ether_addr(mac_addr))
		return -EADDRNOTAVAIL;

	/* If datapath is down, pretend everything went through */
	if (!bnad->rx_info[0].rx)
		return 0;

	ret = bna_rx_ucast_set(bnad->rx_info[0].rx, mac_addr);
	if (ret != BNA_CB_SUCCESS)
		return -EADDRNOTAVAIL;

	return 0;
}