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
struct ef4_nic {int /*<<< orphan*/  net_dev; } ;
typedef  int /*<<< orphan*/  ef4_oword_t ;

/* Variables and functions */
 int /*<<< orphan*/  EF4_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EF4_POPULATE_OWORD_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EF4_SET_OWORD_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FRF_AB_GPIO1_OEN ; 
 int /*<<< orphan*/  FRF_AB_GPIO1_OUT ; 
 int /*<<< orphan*/  FRF_AZ_SRM_INIT_EN ; 
 int /*<<< orphan*/  FRF_AZ_SRM_NB_SZ ; 
 int /*<<< orphan*/  FR_AB_GPIO_CTL ; 
 int /*<<< orphan*/  FR_AZ_SRM_CFG ; 
 int HZ ; 
 int /*<<< orphan*/  ef4_reado (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ef4_writeo (struct ef4_nic*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw ; 
 int /*<<< orphan*/  netif_dbg (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  netif_err (struct ef4_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int) ; 

__attribute__((used)) static int falcon_reset_sram(struct ef4_nic *efx)
{
	ef4_oword_t srm_cfg_reg_ker, gpio_cfg_reg_ker;
	int count;

	/* Set the SRAM wake/sleep GPIO appropriately. */
	ef4_reado(efx, &gpio_cfg_reg_ker, FR_AB_GPIO_CTL);
	EF4_SET_OWORD_FIELD(gpio_cfg_reg_ker, FRF_AB_GPIO1_OEN, 1);
	EF4_SET_OWORD_FIELD(gpio_cfg_reg_ker, FRF_AB_GPIO1_OUT, 1);
	ef4_writeo(efx, &gpio_cfg_reg_ker, FR_AB_GPIO_CTL);

	/* Initiate SRAM reset */
	EF4_POPULATE_OWORD_2(srm_cfg_reg_ker,
			     FRF_AZ_SRM_INIT_EN, 1,
			     FRF_AZ_SRM_NB_SZ, 0);
	ef4_writeo(efx, &srm_cfg_reg_ker, FR_AZ_SRM_CFG);

	/* Wait for SRAM reset to complete */
	count = 0;
	do {
		netif_dbg(efx, hw, efx->net_dev,
			  "waiting for SRAM reset (attempt %d)...\n", count);

		/* SRAM reset is slow; expect around 16ms */
		schedule_timeout_uninterruptible(HZ / 50);

		/* Check for reset complete */
		ef4_reado(efx, &srm_cfg_reg_ker, FR_AZ_SRM_CFG);
		if (!EF4_OWORD_FIELD(srm_cfg_reg_ker, FRF_AZ_SRM_INIT_EN)) {
			netif_dbg(efx, hw, efx->net_dev,
				  "SRAM reset complete\n");

			return 0;
		}
	} while (++count < 20);	/* wait up to 0.4 sec */

	netif_err(efx, hw, efx->net_dev, "timed out waiting for SRAM reset\n");
	return -ETIMEDOUT;
}