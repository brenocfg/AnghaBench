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
struct iwl_rx_phy_res {int dummy; } ;
struct iwl_rx_packet {int /*<<< orphan*/  data; } ;
struct iwl_rx_cmd_buffer {int dummy; } ;
struct iwl_priv {int last_phy_res_valid; int /*<<< orphan*/  last_phy_res; int /*<<< orphan*/  ampdu_ref; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct iwl_rx_packet* rxb_addr (struct iwl_rx_cmd_buffer*) ; 

__attribute__((used)) static void iwlagn_rx_reply_rx_phy(struct iwl_priv *priv,
				   struct iwl_rx_cmd_buffer *rxb)
{
	struct iwl_rx_packet *pkt = rxb_addr(rxb);

	priv->last_phy_res_valid = true;
	priv->ampdu_ref++;
	memcpy(&priv->last_phy_res, pkt->data,
	       sizeof(struct iwl_rx_phy_res));
}