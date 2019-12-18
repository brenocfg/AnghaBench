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
struct sdio_func {int /*<<< orphan*/  dev; } ;
struct if_sdio_packet {scalar_t__ model; struct if_sdio_packet* next; struct if_sdio_packet* packets; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  priv; } ;
struct if_sdio_card {scalar_t__ model; struct if_sdio_card* next; struct if_sdio_card* packets; int /*<<< orphan*/  workqueue; int /*<<< orphan*/  priv; } ;
struct cmd_header {int dummy; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_FUNC_SHUTDOWN ; 
 scalar_t__ MODEL_8688 ; 
 scalar_t__ __lbs_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cmd_header*,int,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct if_sdio_packet*) ; 
 int /*<<< orphan*/  lbs_cmd_copyback ; 
 int /*<<< orphan*/  lbs_deb_sdio (char*) ; 
 int /*<<< orphan*/  lbs_remove_card (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbs_stop_card (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct cmd_header*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_get_noresume (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_alert (char*) ; 
 struct if_sdio_packet* sdio_get_drvdata (struct sdio_func*) ; 
 scalar_t__ user_rmmod ; 

__attribute__((used)) static void if_sdio_remove(struct sdio_func *func)
{
	struct if_sdio_card *card;
	struct if_sdio_packet *packet;

	card = sdio_get_drvdata(func);

	/* Undo decrement done above in if_sdio_probe */
	pm_runtime_get_noresume(&func->dev);

	if (user_rmmod && (card->model == MODEL_8688)) {
		/*
		 * FUNC_SHUTDOWN is required for SD8688 WLAN/BT
		 * multiple functions
		 */
		struct cmd_header cmd;

		memset(&cmd, 0, sizeof(cmd));

		lbs_deb_sdio("send function SHUTDOWN command\n");
		if (__lbs_cmd(card->priv, CMD_FUNC_SHUTDOWN,
				&cmd, sizeof(cmd), lbs_cmd_copyback,
				(unsigned long) &cmd))
			pr_alert("CMD_FUNC_SHUTDOWN cmd failed\n");
	}


	lbs_deb_sdio("call remove card\n");
	lbs_stop_card(card->priv);
	lbs_remove_card(card->priv);

	destroy_workqueue(card->workqueue);

	while (card->packets) {
		packet = card->packets;
		card->packets = card->packets->next;
		kfree(packet);
	}

	kfree(card);
}