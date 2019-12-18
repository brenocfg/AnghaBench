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
struct mmc_card {int /*<<< orphan*/  host; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MMC_SEND_CSD ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 
 int mmc_send_cxd_data (struct mmc_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mmc_spi_send_csd(struct mmc_card *card, u32 *csd)
{
	int ret, i;
	__be32 *csd_tmp;

	csd_tmp = kzalloc(16, GFP_KERNEL);
	if (!csd_tmp)
		return -ENOMEM;

	ret = mmc_send_cxd_data(card, card->host, MMC_SEND_CSD, csd_tmp, 16);
	if (ret)
		goto err;

	for (i = 0; i < 4; i++)
		csd[i] = be32_to_cpu(csd_tmp[i]);

err:
	kfree(csd_tmp);
	return ret;
}