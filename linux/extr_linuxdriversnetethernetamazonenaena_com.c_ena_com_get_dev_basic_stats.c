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
struct TYPE_2__ {int /*<<< orphan*/  basic_stats; } ;
struct ena_com_stats_ctx {TYPE_1__ get_resp; } ;
struct ena_com_dev {int dummy; } ;
struct ena_admin_basic_stats {int dummy; } ;
typedef  int /*<<< orphan*/  ctx ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_ADMIN_GET_STATS_TYPE_BASIC ; 
 int ena_get_dev_stats (struct ena_com_dev*,struct ena_com_stats_ctx*,int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  memcpy (struct ena_admin_basic_stats*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct ena_com_stats_ctx*,int,int) ; 

int ena_com_get_dev_basic_stats(struct ena_com_dev *ena_dev,
				struct ena_admin_basic_stats *stats)
{
	struct ena_com_stats_ctx ctx;
	int ret;

	memset(&ctx, 0x0, sizeof(ctx));
	ret = ena_get_dev_stats(ena_dev, &ctx, ENA_ADMIN_GET_STATS_TYPE_BASIC);
	if (likely(ret == 0))
		memcpy(stats, &ctx.get_resp.basic_stats,
		       sizeof(ctx.get_resp.basic_stats));

	return ret;
}