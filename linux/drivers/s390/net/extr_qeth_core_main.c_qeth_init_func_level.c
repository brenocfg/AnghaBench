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
struct TYPE_2__ {int type; int /*<<< orphan*/  func_level; } ;
struct qeth_card {TYPE_1__ info; } ;

/* Variables and functions */
#define  QETH_CARD_TYPE_IQD 130 
#define  QETH_CARD_TYPE_OSD 129 
#define  QETH_CARD_TYPE_OSN 128 
 int /*<<< orphan*/  QETH_IDX_FUNC_LEVEL_IQD ; 
 int /*<<< orphan*/  QETH_IDX_FUNC_LEVEL_OSD ; 

__attribute__((used)) static void qeth_init_func_level(struct qeth_card *card)
{
	switch (card->info.type) {
	case QETH_CARD_TYPE_IQD:
		card->info.func_level =	QETH_IDX_FUNC_LEVEL_IQD;
		break;
	case QETH_CARD_TYPE_OSD:
	case QETH_CARD_TYPE_OSN:
		card->info.func_level = QETH_IDX_FUNC_LEVEL_OSD;
		break;
	default:
		break;
	}
}