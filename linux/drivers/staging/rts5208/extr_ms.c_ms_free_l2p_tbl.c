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
struct ms_info {int segment_cnt; TYPE_1__* segment; } ;
struct rtsx_chip {struct ms_info ms_card; } ;
struct TYPE_2__ {struct TYPE_2__* free_table; struct TYPE_2__* l2p_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  vfree (TYPE_1__*) ; 

void ms_free_l2p_tbl(struct rtsx_chip *chip)
{
	struct ms_info *ms_card = &chip->ms_card;
	int i = 0;

	if (ms_card->segment) {
		for (i = 0; i < ms_card->segment_cnt; i++) {
			vfree(ms_card->segment[i].l2p_table);
			ms_card->segment[i].l2p_table = NULL;
			vfree(ms_card->segment[i].free_table);
			ms_card->segment[i].free_table = NULL;
		}
		vfree(ms_card->segment);
		ms_card->segment = NULL;
	}
}