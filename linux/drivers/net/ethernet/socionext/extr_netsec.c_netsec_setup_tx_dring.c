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
struct netsec_priv {struct netsec_desc_ring* desc_ring; } ;
struct netsec_desc_ring {struct netsec_de* vaddr; } ;
struct netsec_de {unsigned int attr; } ;

/* Variables and functions */
 int DESC_NUM ; 
 int DESC_SZ ; 
 size_t NETSEC_RING_TX ; 
 unsigned int NETSEC_TX_SHIFT_OWN_FIELD ; 

__attribute__((used)) static void netsec_setup_tx_dring(struct netsec_priv *priv)
{
	struct netsec_desc_ring *dring = &priv->desc_ring[NETSEC_RING_TX];
	int i;

	for (i = 0; i < DESC_NUM; i++) {
		struct netsec_de *de;

		de = dring->vaddr + (DESC_SZ * i);
		/* de->attr is not going to be accessed by the NIC
		 * until netsec_set_tx_de() is called.
		 * No need for a dma_wmb() here
		 */
		de->attr = 1U << NETSEC_TX_SHIFT_OWN_FIELD;
	}
}