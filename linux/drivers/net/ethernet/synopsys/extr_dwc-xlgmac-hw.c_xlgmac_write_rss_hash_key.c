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
struct xlgmac_pdata {int /*<<< orphan*/  rss_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  XLGMAC_RSS_HASH_KEY_TYPE ; 
 int xlgmac_write_rss_reg (struct xlgmac_pdata*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xlgmac_write_rss_hash_key(struct xlgmac_pdata *pdata)
{
	unsigned int key_regs = sizeof(pdata->rss_key) / sizeof(u32);
	unsigned int *key = (unsigned int *)&pdata->rss_key;
	int ret;

	while (key_regs--) {
		ret = xlgmac_write_rss_reg(pdata, XLGMAC_RSS_HASH_KEY_TYPE,
					   key_regs, *key++);
		if (ret)
			return ret;
	}

	return 0;
}