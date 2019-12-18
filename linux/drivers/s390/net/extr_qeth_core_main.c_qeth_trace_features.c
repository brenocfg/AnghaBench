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
struct TYPE_3__ {int /*<<< orphan*/  diagass_support; } ;
struct TYPE_4__ {int /*<<< orphan*/  adp; int /*<<< orphan*/  ipa6; int /*<<< orphan*/  ipa4; } ;
struct qeth_card {TYPE_1__ info; TYPE_2__ options; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_HEX (struct qeth_card*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 

void qeth_trace_features(struct qeth_card *card)
{
	QETH_CARD_TEXT(card, 2, "features");
	QETH_CARD_HEX(card, 2, &card->options.ipa4, sizeof(card->options.ipa4));
	QETH_CARD_HEX(card, 2, &card->options.ipa6, sizeof(card->options.ipa6));
	QETH_CARD_HEX(card, 2, &card->options.adp, sizeof(card->options.adp));
	QETH_CARD_HEX(card, 2, &card->info.diagass_support,
		      sizeof(card->info.diagass_support));
}