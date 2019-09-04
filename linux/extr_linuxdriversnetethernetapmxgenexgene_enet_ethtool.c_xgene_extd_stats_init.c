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
typedef  int /*<<< orphan*/  u64 ;
struct xgene_enet_pdata {int /*<<< orphan*/  extd_stats; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int XGENE_EXTD_STATS_LEN ; 
 int /*<<< orphan*/  devm_kmalloc_array (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xgene_get_extd_stats (struct xgene_enet_pdata*) ; 

int xgene_extd_stats_init(struct xgene_enet_pdata *pdata)
{
	pdata->extd_stats = devm_kmalloc_array(&pdata->pdev->dev,
			XGENE_EXTD_STATS_LEN, sizeof(u64), GFP_KERNEL);
	if (!pdata->extd_stats)
		return -ENOMEM;

	xgene_get_extd_stats(pdata);
	memset(pdata->extd_stats, 0, XGENE_EXTD_STATS_LEN * sizeof(u64));

	return 0;
}