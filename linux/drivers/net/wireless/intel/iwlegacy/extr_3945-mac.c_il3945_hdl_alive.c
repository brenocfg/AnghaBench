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
struct il_alive_resp {scalar_t__ is_valid; scalar_t__ ver_subtype; int /*<<< orphan*/  ver_type; } ;
struct TYPE_2__ {struct il_alive_resp alive_frame; } ;
struct il_rx_pkt {TYPE_1__ u; } ;
struct il_rx_buf {int dummy; } ;
struct delayed_work {int dummy; } ;
struct il_priv {int /*<<< orphan*/  workqueue; struct delayed_work alive_start; int /*<<< orphan*/  card_alive; struct delayed_work init_alive_start; int /*<<< orphan*/  card_alive_init; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_INFO (char*,...) ; 
 int /*<<< orphan*/  IL_WARN (char*) ; 
 scalar_t__ INITIALIZE_SUBTYPE ; 
 scalar_t__ UCODE_VALID_OK ; 
 int /*<<< orphan*/  il3945_disable_events (struct il_priv*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct il_alive_resp*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,struct delayed_work*,int /*<<< orphan*/ ) ; 
 struct il_rx_pkt* rxb_addr (struct il_rx_buf*) ; 

__attribute__((used)) static void
il3945_hdl_alive(struct il_priv *il, struct il_rx_buf *rxb)
{
	struct il_rx_pkt *pkt = rxb_addr(rxb);
	struct il_alive_resp *palive;
	struct delayed_work *pwork;

	palive = &pkt->u.alive_frame;

	D_INFO("Alive ucode status 0x%08X revision " "0x%01X 0x%01X\n",
	       palive->is_valid, palive->ver_type, palive->ver_subtype);

	if (palive->ver_subtype == INITIALIZE_SUBTYPE) {
		D_INFO("Initialization Alive received.\n");
		memcpy(&il->card_alive_init, &pkt->u.alive_frame,
		       sizeof(struct il_alive_resp));
		pwork = &il->init_alive_start;
	} else {
		D_INFO("Runtime Alive received.\n");
		memcpy(&il->card_alive, &pkt->u.alive_frame,
		       sizeof(struct il_alive_resp));
		pwork = &il->alive_start;
		il3945_disable_events(il);
	}

	/* We delay the ALIVE response by 5ms to
	 * give the HW RF Kill time to activate... */
	if (palive->is_valid == UCODE_VALID_OK)
		queue_delayed_work(il->workqueue, pwork, msecs_to_jiffies(5));
	else
		IL_WARN("uCode did not respond OK.\n");
}