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
struct xd_info {int zone_cnt; TYPE_1__* zone; } ;
struct rtsx_chip {struct xd_info xd_card; } ;
struct TYPE_2__ {struct TYPE_2__* free_table; struct TYPE_2__* l2p_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfree (TYPE_1__*) ; 

void xd_free_l2p_tbl(struct rtsx_chip *chip)
{
	struct xd_info *xd_card = &chip->xd_card;
	int i = 0;

	if (xd_card->zone) {
		for (i = 0; i < xd_card->zone_cnt; i++) {
			vfree(xd_card->zone[i].l2p_table);
			xd_card->zone[i].l2p_table = NULL;
			vfree(xd_card->zone[i].free_table);
			xd_card->zone[i].free_table = NULL;
		}
		vfree(xd_card->zone);
		xd_card->zone = NULL;
	}
}