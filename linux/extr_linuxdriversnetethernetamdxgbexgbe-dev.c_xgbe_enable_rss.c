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
struct TYPE_2__ {int /*<<< orphan*/  rss; } ;
struct xgbe_prv_data {int /*<<< orphan*/  rss_options; TYPE_1__ hw_feat; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  MAC_RSSCR ; 
 int /*<<< orphan*/  RSSE ; 
 int /*<<< orphan*/  XGMAC_IOWRITE (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XGMAC_IOWRITE_BITS (struct xgbe_prv_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int xgbe_write_rss_hash_key (struct xgbe_prv_data*) ; 
 int xgbe_write_rss_lookup_table (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_enable_rss(struct xgbe_prv_data *pdata)
{
	int ret;

	if (!pdata->hw_feat.rss)
		return -EOPNOTSUPP;

	/* Program the hash key */
	ret = xgbe_write_rss_hash_key(pdata);
	if (ret)
		return ret;

	/* Program the lookup table */
	ret = xgbe_write_rss_lookup_table(pdata);
	if (ret)
		return ret;

	/* Set the RSS options */
	XGMAC_IOWRITE(pdata, MAC_RSSCR, pdata->rss_options);

	/* Enable RSS */
	XGMAC_IOWRITE_BITS(pdata, MAC_RSSCR, RSSE, 1);

	return 0;
}