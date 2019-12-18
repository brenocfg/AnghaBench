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
typedef  size_t u32 ;
struct stmmac_rx_queue {int /*<<< orphan*/  page_pool; struct stmmac_rx_buffer* buf_pool; } ;
struct stmmac_rx_buffer {int /*<<< orphan*/ * sec_page; int /*<<< orphan*/ * page; } ;
struct stmmac_priv {struct stmmac_rx_queue* rx_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  page_pool_put_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void stmmac_free_rx_buffer(struct stmmac_priv *priv, u32 queue, int i)
{
	struct stmmac_rx_queue *rx_q = &priv->rx_queue[queue];
	struct stmmac_rx_buffer *buf = &rx_q->buf_pool[i];

	if (buf->page)
		page_pool_put_page(rx_q->page_pool, buf->page, false);
	buf->page = NULL;

	if (buf->sec_page)
		page_pool_put_page(rx_q->page_pool, buf->sec_page, false);
	buf->sec_page = NULL;
}