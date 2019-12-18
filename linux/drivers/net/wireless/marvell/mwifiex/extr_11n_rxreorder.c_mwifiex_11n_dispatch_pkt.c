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
struct sk_buff {int dummy; } ;
struct mwifiex_private {scalar_t__ bss_role; int /*<<< orphan*/  adapter; } ;

/* Variables and functions */
 int /*<<< orphan*/  INFO ; 
 scalar_t__ MWIFIEX_BSS_ROLE_UAP ; 
 int mwifiex_11n_dispatch_amsdu_pkt (struct mwifiex_private*,struct sk_buff*) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int mwifiex_handle_uap_rx_forward (struct mwifiex_private*,struct sk_buff*) ; 
 int mwifiex_process_rx_packet (struct mwifiex_private*,struct sk_buff*) ; 

__attribute__((used)) static int mwifiex_11n_dispatch_pkt(struct mwifiex_private *priv,
				    struct sk_buff *payload)
{

	int ret;

	if (!payload) {
		mwifiex_dbg(priv->adapter, INFO, "info: fw drop data\n");
		return 0;
	}

	ret = mwifiex_11n_dispatch_amsdu_pkt(priv, payload);
	if (!ret)
		return 0;

	if (priv->bss_role == MWIFIEX_BSS_ROLE_UAP)
		return mwifiex_handle_uap_rx_forward(priv, payload);

	return mwifiex_process_rx_packet(priv, payload);
}