#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct bnad {int num_rxp_per_rx; TYPE_2__* rx_info; } ;
struct TYPE_4__ {TYPE_1__* rx_ctrl; } ;
struct TYPE_3__ {int /*<<< orphan*/  napi; } ;

/* Variables and functions */
 int /*<<< orphan*/  netif_napi_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bnad_napi_delete(struct bnad *bnad, u32 rx_id)
{
	int i;

	/* First disable and then clean up */
	for (i = 0; i < bnad->num_rxp_per_rx; i++)
		netif_napi_del(&bnad->rx_info[rx_id].rx_ctrl[i].napi);
}