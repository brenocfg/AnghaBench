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
typedef  size_t u32 ;
struct gve_queue_page_list {size_t id; int num_entries; int /*<<< orphan*/ * page_buses; int /*<<< orphan*/ * pages; } ;
struct gve_priv {scalar_t__ num_registered_pages; scalar_t__ max_registered_pages; TYPE_1__* pdev; int /*<<< orphan*/  dev; struct gve_queue_page_list* qpls; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  drv ; 
 int gve_alloc_page (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gve_qpl_dma_dir (struct gve_priv*,size_t) ; 
 void* kvzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_err (struct gve_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int gve_alloc_queue_page_list(struct gve_priv *priv, u32 id,
				     int pages)
{
	struct gve_queue_page_list *qpl = &priv->qpls[id];
	int err;
	int i;

	if (pages + priv->num_registered_pages > priv->max_registered_pages) {
		netif_err(priv, drv, priv->dev,
			  "Reached max number of registered pages %llu > %llu\n",
			  pages + priv->num_registered_pages,
			  priv->max_registered_pages);
		return -EINVAL;
	}

	qpl->id = id;
	qpl->num_entries = pages;
	qpl->pages = kvzalloc(pages * sizeof(*qpl->pages), GFP_KERNEL);
	/* caller handles clean up */
	if (!qpl->pages)
		return -ENOMEM;
	qpl->page_buses = kvzalloc(pages * sizeof(*qpl->page_buses),
				   GFP_KERNEL);
	/* caller handles clean up */
	if (!qpl->page_buses)
		return -ENOMEM;

	for (i = 0; i < pages; i++) {
		err = gve_alloc_page(&priv->pdev->dev, &qpl->pages[i],
				     &qpl->page_buses[i],
				     gve_qpl_dma_dir(priv, id));
		/* caller handles clean up */
		if (err)
			return -ENOMEM;
	}
	priv->num_registered_pages += pages;

	return 0;
}