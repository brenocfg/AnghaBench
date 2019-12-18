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
struct xgbe_prv_data {int /*<<< orphan*/ * rss_table; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  XGBE_RSS_LOOKUP_TABLE_TYPE ; 
 int xgbe_write_rss_reg (struct xgbe_prv_data*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgbe_write_rss_lookup_table(struct xgbe_prv_data *pdata)
{
	unsigned int i;
	int ret;

	for (i = 0; i < ARRAY_SIZE(pdata->rss_table); i++) {
		ret = xgbe_write_rss_reg(pdata,
					 XGBE_RSS_LOOKUP_TABLE_TYPE, i,
					 pdata->rss_table[i]);
		if (ret)
			return ret;
	}

	return 0;
}