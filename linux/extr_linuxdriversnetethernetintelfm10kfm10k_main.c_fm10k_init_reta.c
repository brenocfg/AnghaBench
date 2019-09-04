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
typedef  int u32 ;
typedef  size_t u16 ;
struct fm10k_intfc {int* reta; TYPE_1__* pdev; int /*<<< orphan*/  netdev; TYPE_2__* ring_feature; } ;
struct TYPE_4__ {size_t indices; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t FM10K_RETA_SIZE ; 
 size_t RING_F_RSS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fm10k_write_reta (struct fm10k_intfc*,int /*<<< orphan*/ *) ; 
 scalar_t__ netif_is_rxfh_configured (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fm10k_init_reta(struct fm10k_intfc *interface)
{
	u16 i, rss_i = interface->ring_feature[RING_F_RSS].indices;
	u32 reta;

	/* If the Rx flow indirection table has been configured manually, we
	 * need to maintain it when possible.
	 */
	if (netif_is_rxfh_configured(interface->netdev)) {
		for (i = FM10K_RETA_SIZE; i--;) {
			reta = interface->reta[i];
			if ((((reta << 24) >> 24) < rss_i) &&
			    (((reta << 16) >> 24) < rss_i) &&
			    (((reta <<  8) >> 24) < rss_i) &&
			    (((reta)       >> 24) < rss_i))
				continue;

			/* this should never happen */
			dev_err(&interface->pdev->dev,
				"RSS indirection table assigned flows out of queue bounds. Reconfiguring.\n");
			goto repopulate_reta;
		}

		/* do nothing if all of the elements are in bounds */
		return;
	}

repopulate_reta:
	fm10k_write_reta(interface, NULL);
}