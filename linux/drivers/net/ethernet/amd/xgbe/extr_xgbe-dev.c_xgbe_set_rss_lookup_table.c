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
typedef  int /*<<< orphan*/  u32 ;
struct xgbe_prv_data {int /*<<< orphan*/ * rss_table; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DMCH ; 
 int /*<<< orphan*/  MAC_RSSDR ; 
 int /*<<< orphan*/  XGMAC_SET_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 
 int xgbe_write_rss_lookup_table (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_set_rss_lookup_table(struct xgbe_prv_data *pdata,
				     const u32 *table)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(pdata->rss_table); i++)
		XGMAC_SET_BITS(pdata->rss_table[i], MAC_RSSDR, DMCH, table[i]);

	return xgbe_write_rss_lookup_table(pdata);
}