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
struct xdp_rxq_info {int dummy; } ;
struct page_pool {int dummy; } ;
struct cpsw_priv {int /*<<< orphan*/  ndev; struct xdp_rxq_info* xdp_rxq; struct cpsw_common* cpsw; } ;
struct cpsw_common {struct page_pool** page_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_TYPE_PAGE_POOL ; 
 int xdp_rxq_info_reg (struct xdp_rxq_info*,int /*<<< orphan*/ ,int) ; 
 int xdp_rxq_info_reg_mem_model (struct xdp_rxq_info*,int /*<<< orphan*/ ,struct page_pool*) ; 
 int /*<<< orphan*/  xdp_rxq_info_unreg (struct xdp_rxq_info*) ; 

__attribute__((used)) static int cpsw_ndev_create_xdp_rxq(struct cpsw_priv *priv, int ch)
{
	struct cpsw_common *cpsw = priv->cpsw;
	struct xdp_rxq_info *rxq;
	struct page_pool *pool;
	int ret;

	pool = cpsw->page_pool[ch];
	rxq = &priv->xdp_rxq[ch];

	ret = xdp_rxq_info_reg(rxq, priv->ndev, ch);
	if (ret)
		return ret;

	ret = xdp_rxq_info_reg_mem_model(rxq, MEM_TYPE_PAGE_POOL, pool);
	if (ret)
		xdp_rxq_info_unreg(rxq);

	return ret;
}