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
struct stmmac_rx_queue {struct stmmac_priv* priv_data; } ;
struct stmmac_priv {scalar_t__ dma_buf_sz; } ;
struct dma_desc {int /*<<< orphan*/  des2; int /*<<< orphan*/  des3; } ;

/* Variables and functions */
 scalar_t__ BUF_SIZE_16KiB ; 
 scalar_t__ BUF_SIZE_8KiB ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void refill_desc3(void *priv_ptr, struct dma_desc *p)
{
	struct stmmac_rx_queue *rx_q = priv_ptr;
	struct stmmac_priv *priv = rx_q->priv_data;

	/* Fill DES3 in case of RING mode */
	if (priv->dma_buf_sz == BUF_SIZE_16KiB)
		p->des3 = cpu_to_le32(le32_to_cpu(p->des2) + BUF_SIZE_8KiB);
}