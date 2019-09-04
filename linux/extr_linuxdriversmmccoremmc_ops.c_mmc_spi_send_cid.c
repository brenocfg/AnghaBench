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
struct mmc_host {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MMC_SEND_CID ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int mmc_send_cxd_data (int /*<<< orphan*/ *,struct mmc_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mmc_spi_send_cid(struct mmc_host *host, u32 *cid)
{
	int ret, i;
	__be32 *cid_tmp;

	cid_tmp = kzalloc(16, GFP_KERNEL);
	if (!cid_tmp)
		return -ENOMEM;

	ret = mmc_send_cxd_data(NULL, host, MMC_SEND_CID, cid_tmp, 16);
	if (ret)
		goto err;

	for (i = 0; i < 4; i++)
		cid[i] = be32_to_cpu(cid_tmp[i]);

err:
	kfree(cid_tmp);
	return ret;
}