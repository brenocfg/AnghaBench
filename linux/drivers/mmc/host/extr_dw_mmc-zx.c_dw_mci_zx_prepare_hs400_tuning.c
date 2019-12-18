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
struct mmc_ios {int dummy; } ;
struct dw_mci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY_TYPE_READ ; 
 int EIO ; 
 int dw_mci_zx_emmc_set_delay (struct dw_mci*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dw_mci_zx_prepare_hs400_tuning(struct dw_mci *host,
					  struct mmc_ios *ios)
{
	int ret;

	/* config phase shift as 90 degree */
	ret = dw_mci_zx_emmc_set_delay(host, 32, DELAY_TYPE_READ);
	if (ret < 0)
		return -EIO;

	return 0;
}