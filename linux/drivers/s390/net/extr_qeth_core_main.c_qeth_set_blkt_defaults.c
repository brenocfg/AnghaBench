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
struct TYPE_3__ {int time_total; int inter_packet; int inter_packet_jumbo; } ;
struct TYPE_4__ {TYPE_1__ blkt; scalar_t__ use_v1_blkt; } ;
struct qeth_card {TYPE_2__ info; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 

__attribute__((used)) static void qeth_set_blkt_defaults(struct qeth_card *card)
{
	QETH_CARD_TEXT(card, 2, "cfgblkt");

	if (card->info.use_v1_blkt) {
		card->info.blkt.time_total = 0;
		card->info.blkt.inter_packet = 0;
		card->info.blkt.inter_packet_jumbo = 0;
	} else {
		card->info.blkt.time_total = 250;
		card->info.blkt.inter_packet = 5;
		card->info.blkt.inter_packet_jumbo = 15;
	}
}