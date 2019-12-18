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
struct lbs_private {struct if_sdio_card* card; } ;
struct if_sdio_card {TYPE_2__* func; } ;
struct TYPE_4__ {TYPE_1__* card; } ;
struct TYPE_3__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 int /*<<< orphan*/  card_reset_work ; 
 int /*<<< orphan*/  reset_host ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 scalar_t__ work_pending (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void if_sdio_reset_card(struct lbs_private *priv)
{
	struct if_sdio_card *card = priv->card;

	if (work_pending(&card_reset_work))
		return;

	reset_host = card->func->card->host;
	schedule_work(&card_reset_work);
}