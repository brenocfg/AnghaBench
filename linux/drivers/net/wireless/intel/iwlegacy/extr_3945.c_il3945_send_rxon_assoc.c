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
struct il_rxon_cmd {scalar_t__ flags; scalar_t__ filter_flags; scalar_t__ cck_basic_rates; scalar_t__ ofdm_basic_rates; } ;
struct TYPE_2__ {int flags; } ;
struct il_rx_pkt {TYPE_1__ hdr; } ;
struct il_priv {struct il_rxon_cmd staging; struct il_rxon_cmd active; } ;
struct il_host_cmd {int len; scalar_t__ reply_page; struct il3945_rxon_assoc_cmd* data; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; } ;
struct il3945_rxon_assoc_cmd {scalar_t__ flags; scalar_t__ filter_flags; scalar_t__ ofdm_basic_rates; scalar_t__ cck_basic_rates; scalar_t__ reserved; } ;
typedef  int /*<<< orphan*/  rxon_assoc ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_WANT_SKB ; 
 int /*<<< orphan*/  C_RXON_ASSOC ; 
 int /*<<< orphan*/  D_INFO (char*) ; 
 int EIO ; 
 int IL_CMD_FAILED_MSK ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 int /*<<< orphan*/  il_free_pages (struct il_priv*,scalar_t__) ; 
 int il_send_cmd_sync (struct il_priv*,struct il_host_cmd*) ; 

__attribute__((used)) static int
il3945_send_rxon_assoc(struct il_priv *il)
{
	int rc = 0;
	struct il_rx_pkt *pkt;
	struct il3945_rxon_assoc_cmd rxon_assoc;
	struct il_host_cmd cmd = {
		.id = C_RXON_ASSOC,
		.len = sizeof(rxon_assoc),
		.flags = CMD_WANT_SKB,
		.data = &rxon_assoc,
	};
	const struct il_rxon_cmd *rxon1 = &il->staging;
	const struct il_rxon_cmd *rxon2 = &il->active;

	if (rxon1->flags == rxon2->flags &&
	    rxon1->filter_flags == rxon2->filter_flags &&
	    rxon1->cck_basic_rates == rxon2->cck_basic_rates &&
	    rxon1->ofdm_basic_rates == rxon2->ofdm_basic_rates) {
		D_INFO("Using current RXON_ASSOC.  Not resending.\n");
		return 0;
	}

	rxon_assoc.flags = il->staging.flags;
	rxon_assoc.filter_flags = il->staging.filter_flags;
	rxon_assoc.ofdm_basic_rates = il->staging.ofdm_basic_rates;
	rxon_assoc.cck_basic_rates = il->staging.cck_basic_rates;
	rxon_assoc.reserved = 0;

	rc = il_send_cmd_sync(il, &cmd);
	if (rc)
		return rc;

	pkt = (struct il_rx_pkt *)cmd.reply_page;
	if (pkt->hdr.flags & IL_CMD_FAILED_MSK) {
		IL_ERR("Bad return from C_RXON_ASSOC command\n");
		rc = -EIO;
	}

	il_free_pages(il, cmd.reply_page);

	return rc;
}