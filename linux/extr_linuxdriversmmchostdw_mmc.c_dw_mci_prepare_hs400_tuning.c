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
struct mmc_host {int dummy; } ;
struct dw_mci_slot {struct dw_mci* host; } ;
struct dw_mci_drv_data {int (* prepare_hs400_tuning ) (struct dw_mci*,struct mmc_ios*) ;} ;
struct dw_mci {struct dw_mci_drv_data* drv_data; } ;

/* Variables and functions */
 struct dw_mci_slot* mmc_priv (struct mmc_host*) ; 
 int stub1 (struct dw_mci*,struct mmc_ios*) ; 

__attribute__((used)) static int dw_mci_prepare_hs400_tuning(struct mmc_host *mmc,
				       struct mmc_ios *ios)
{
	struct dw_mci_slot *slot = mmc_priv(mmc);
	struct dw_mci *host = slot->host;
	const struct dw_mci_drv_data *drv_data = host->drv_data;

	if (drv_data && drv_data->prepare_hs400_tuning)
		return drv_data->prepare_hs400_tuning(host, ios);

	return 0;
}