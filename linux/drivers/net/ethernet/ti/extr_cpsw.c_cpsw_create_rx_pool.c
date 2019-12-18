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
struct page_pool {int dummy; } ;
struct cpsw_common {struct page_pool** page_pool; TYPE_1__* rxv; } ;
struct TYPE_2__ {int /*<<< orphan*/  ch; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct page_pool*) ; 
 int PTR_ERR (struct page_pool*) ; 
 int cpdma_chan_get_rx_buf_num (int /*<<< orphan*/ ) ; 
 struct page_pool* cpsw_create_page_pool (struct cpsw_common*,int) ; 

__attribute__((used)) static int cpsw_create_rx_pool(struct cpsw_common *cpsw, int ch)
{
	struct page_pool *pool;
	int ret = 0, pool_size;

	pool_size = cpdma_chan_get_rx_buf_num(cpsw->rxv[ch].ch);
	pool = cpsw_create_page_pool(cpsw, pool_size);
	if (IS_ERR(pool))
		ret = PTR_ERR(pool);
	else
		cpsw->page_pool[ch] = pool;

	return ret;
}