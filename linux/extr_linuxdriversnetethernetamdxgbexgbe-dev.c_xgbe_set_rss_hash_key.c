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
typedef  int /*<<< orphan*/  u8 ;
struct xgbe_prv_data {int /*<<< orphan*/  rss_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int) ; 
 int xgbe_write_rss_hash_key (struct xgbe_prv_data*) ; 

__attribute__((used)) static int xgbe_set_rss_hash_key(struct xgbe_prv_data *pdata, const u8 *key)
{
	memcpy(pdata->rss_key, key, sizeof(pdata->rss_key));

	return xgbe_write_rss_hash_key(pdata);
}