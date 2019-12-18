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
struct qeth_card {int /*<<< orphan*/  data; int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int qeth_clear_channel (struct qeth_card*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qeth_clear_channels(struct qeth_card *card)
{
	int rc1 = 0, rc2 = 0, rc3 = 0;

	QETH_CARD_TEXT(card, 3, "clearchs");
	rc1 = qeth_clear_channel(card, &card->read);
	rc2 = qeth_clear_channel(card, &card->write);
	rc3 = qeth_clear_channel(card, &card->data);
	if (rc1)
		return rc1;
	if (rc2)
		return rc2;
	return rc3;
}