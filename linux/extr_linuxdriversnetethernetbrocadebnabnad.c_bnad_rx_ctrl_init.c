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
typedef  size_t u32 ;
struct bnad_rx_info {TYPE_1__* rx_ctrl; } ;
struct bnad {int num_rxp_per_rx; struct bnad_rx_info* rx_info; } ;
struct TYPE_2__ {struct bnad* bnad; } ;

/* Variables and functions */

__attribute__((used)) static void
bnad_rx_ctrl_init(struct bnad *bnad, u32 rx_id)
{
	struct bnad_rx_info *rx_info = &bnad->rx_info[rx_id];
	int i;

	for (i = 0; i < bnad->num_rxp_per_rx; i++)
		rx_info->rx_ctrl[i].bnad = bnad;
}