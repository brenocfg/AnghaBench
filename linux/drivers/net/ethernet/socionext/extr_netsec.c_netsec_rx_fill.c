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
typedef  size_t u16 ;
struct netsec_priv {struct netsec_desc_ring* desc_ring; } ;
struct netsec_desc_ring {int /*<<< orphan*/ * desc; } ;

/* Variables and functions */
 size_t DESC_NUM ; 
 size_t NETSEC_RING_RX ; 
 int /*<<< orphan*/  netsec_set_rx_de (struct netsec_priv*,struct netsec_desc_ring*,size_t,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void netsec_rx_fill(struct netsec_priv *priv, u16 from, u16 num)
{
	struct netsec_desc_ring *dring = &priv->desc_ring[NETSEC_RING_RX];
	u16 idx = from;

	while (num) {
		netsec_set_rx_de(priv, dring, idx, &dring->desc[idx]);
		idx++;
		if (idx >= DESC_NUM)
			idx = 0;
		num--;
	}
}