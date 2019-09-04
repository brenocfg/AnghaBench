#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  phys_addr; } ;
struct TYPE_7__ {int /*<<< orphan*/  phys_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  phys_addr; } ;
struct TYPE_5__ {int /*<<< orphan*/  phys_addr; } ;
struct hix5hd2_priv {TYPE_4__ tx_bq; TYPE_3__ tx_rq; TYPE_2__ rx_bq; TYPE_1__ rx_fq; } ;

/* Variables and functions */
 int /*<<< orphan*/  hix5hd2_set_rx_bq (struct hix5hd2_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hix5hd2_set_rx_fq (struct hix5hd2_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hix5hd2_set_tx_bq (struct hix5hd2_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hix5hd2_set_tx_rq (struct hix5hd2_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hix5hd2_set_desc_addr(struct hix5hd2_priv *priv)
{
	hix5hd2_set_rx_fq(priv, priv->rx_fq.phys_addr);
	hix5hd2_set_rx_bq(priv, priv->rx_bq.phys_addr);
	hix5hd2_set_tx_rq(priv, priv->tx_rq.phys_addr);
	hix5hd2_set_tx_bq(priv, priv->tx_bq.phys_addr);
}