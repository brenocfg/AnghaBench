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
struct TYPE_3__ {int /*<<< orphan*/  sent; } ;
struct tx_desc {TYPE_1__ header; } ;
struct TYPE_4__ {int len; scalar_t__ buf; } ;
struct ec_bhf_priv {int tx_dcount; struct tx_desc* tx_descs; scalar_t__ tx_dnext; TYPE_2__ tx_buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  TX_HDR_SENT ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ec_bhf_setup_tx_descs(struct ec_bhf_priv *priv)
{
	int i = 0;

	priv->tx_dcount = priv->tx_buf.len / sizeof(struct tx_desc);
	priv->tx_descs = (struct tx_desc *)priv->tx_buf.buf;
	priv->tx_dnext = 0;

	for (i = 0; i < priv->tx_dcount; i++)
		priv->tx_descs[i].header.sent = cpu_to_le32(TX_HDR_SENT);
}