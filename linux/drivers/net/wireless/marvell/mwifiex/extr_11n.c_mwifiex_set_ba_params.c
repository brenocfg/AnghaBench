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
struct TYPE_2__ {int tx_amsdu; int rx_amsdu; int /*<<< orphan*/  rx_win_size; int /*<<< orphan*/  tx_win_size; int /*<<< orphan*/  timeout; } ;
struct mwifiex_private {TYPE_1__ add_ba_param; } ;

/* Variables and functions */
 scalar_t__ GET_BSS_ROLE (struct mwifiex_private*) ; 
 scalar_t__ MWIFIEX_BSS_ROLE_UAP ; 
 int /*<<< orphan*/  MWIFIEX_DEFAULT_BLOCK_ACK_TIMEOUT ; 
 int /*<<< orphan*/  MWIFIEX_STA_AMPDU_DEF_RXWINSIZE ; 
 int /*<<< orphan*/  MWIFIEX_STA_AMPDU_DEF_TXWINSIZE ; 
 int /*<<< orphan*/  MWIFIEX_UAP_AMPDU_DEF_RXWINSIZE ; 
 int /*<<< orphan*/  MWIFIEX_UAP_AMPDU_DEF_TXWINSIZE ; 

void mwifiex_set_ba_params(struct mwifiex_private *priv)
{
	priv->add_ba_param.timeout = MWIFIEX_DEFAULT_BLOCK_ACK_TIMEOUT;

	if (GET_BSS_ROLE(priv) == MWIFIEX_BSS_ROLE_UAP) {
		priv->add_ba_param.tx_win_size =
						MWIFIEX_UAP_AMPDU_DEF_TXWINSIZE;
		priv->add_ba_param.rx_win_size =
						MWIFIEX_UAP_AMPDU_DEF_RXWINSIZE;
	} else {
		priv->add_ba_param.tx_win_size =
						MWIFIEX_STA_AMPDU_DEF_TXWINSIZE;
		priv->add_ba_param.rx_win_size =
						MWIFIEX_STA_AMPDU_DEF_RXWINSIZE;
	}

	priv->add_ba_param.tx_amsdu = true;
	priv->add_ba_param.rx_amsdu = true;

	return;
}