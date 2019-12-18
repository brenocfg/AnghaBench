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
struct gve_queue_page_list {int num_entries; int /*<<< orphan*/ * pages; int /*<<< orphan*/ * page_buses; } ;
struct gve_priv {int num_registered_pages; TYPE_1__* pdev; struct gve_queue_page_list* qpls; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  gve_free_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gve_qpl_dma_dir (struct gve_priv*,int) ; 
 int /*<<< orphan*/  kvfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gve_free_queue_page_list(struct gve_priv *priv,
				     int id)
{
	struct gve_queue_page_list *qpl = &priv->qpls[id];
	int i;

	if (!qpl->pages)
		return;
	if (!qpl->page_buses)
		goto free_pages;

	for (i = 0; i < qpl->num_entries; i++)
		gve_free_page(&priv->pdev->dev, qpl->pages[i],
			      qpl->page_buses[i], gve_qpl_dma_dir(priv, id));

	kvfree(qpl->page_buses);
free_pages:
	kvfree(qpl->pages);
	priv->num_registered_pages -= qpl->num_entries;
}