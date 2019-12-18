#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct qcom_ethqos {unsigned int num_por; scalar_t__ speed; TYPE_2__* pdev; TYPE_1__* por; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int /*<<< orphan*/  GENMASK (int,int) ; 
 int /*<<< orphan*/  SDC4_STATUS ; 
 unsigned int volatile SDC4_STATUS_DLL_LOCK ; 
 int /*<<< orphan*/  SDCC_DLL_CONFIG_CK_OUT_EN ; 
 int /*<<< orphan*/  SDCC_DLL_CONFIG_DLL_EN ; 
 int /*<<< orphan*/  SDCC_DLL_CONFIG_DLL_RST ; 
 int /*<<< orphan*/  SDCC_DLL_CONFIG_PDN ; 
 int /*<<< orphan*/  SDCC_HC_REG_DLL_CONFIG ; 
 int /*<<< orphan*/  SDCC_USR_CTL ; 
 scalar_t__ SPEED_10 ; 
 scalar_t__ SPEED_100 ; 
 scalar_t__ SPEED_1000 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ethqos_dll_configure (struct qcom_ethqos*) ; 
 int /*<<< orphan*/  ethqos_rgmii_macro_init (struct qcom_ethqos*) ; 
 int /*<<< orphan*/  ethqos_set_func_clk_en (struct qcom_ethqos*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 unsigned int rgmii_readl (struct qcom_ethqos*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgmii_updatel (struct qcom_ethqos*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgmii_writel (struct qcom_ethqos*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ethqos_configure(struct qcom_ethqos *ethqos)
{
	volatile unsigned int dll_lock;
	unsigned int i, retry = 1000;

	/* Reset to POR values and enable clk */
	for (i = 0; i < ethqos->num_por; i++)
		rgmii_writel(ethqos, ethqos->por[i].value,
			     ethqos->por[i].offset);
	ethqos_set_func_clk_en(ethqos);

	/* Initialize the DLL first */

	/* Set DLL_RST */
	rgmii_updatel(ethqos, SDCC_DLL_CONFIG_DLL_RST,
		      SDCC_DLL_CONFIG_DLL_RST, SDCC_HC_REG_DLL_CONFIG);

	/* Set PDN */
	rgmii_updatel(ethqos, SDCC_DLL_CONFIG_PDN,
		      SDCC_DLL_CONFIG_PDN, SDCC_HC_REG_DLL_CONFIG);

	/* Clear DLL_RST */
	rgmii_updatel(ethqos, SDCC_DLL_CONFIG_DLL_RST, 0,
		      SDCC_HC_REG_DLL_CONFIG);

	/* Clear PDN */
	rgmii_updatel(ethqos, SDCC_DLL_CONFIG_PDN, 0,
		      SDCC_HC_REG_DLL_CONFIG);

	if (ethqos->speed != SPEED_100 && ethqos->speed != SPEED_10) {
		/* Set DLL_EN */
		rgmii_updatel(ethqos, SDCC_DLL_CONFIG_DLL_EN,
			      SDCC_DLL_CONFIG_DLL_EN, SDCC_HC_REG_DLL_CONFIG);

		/* Set CK_OUT_EN */
		rgmii_updatel(ethqos, SDCC_DLL_CONFIG_CK_OUT_EN,
			      SDCC_DLL_CONFIG_CK_OUT_EN,
			      SDCC_HC_REG_DLL_CONFIG);

		/* Set USR_CTL bit 26 with mask of 3 bits */
		rgmii_updatel(ethqos, GENMASK(26, 24), BIT(26), SDCC_USR_CTL);

		/* wait for DLL LOCK */
		do {
			mdelay(1);
			dll_lock = rgmii_readl(ethqos, SDC4_STATUS);
			if (dll_lock & SDC4_STATUS_DLL_LOCK)
				break;
		} while (retry > 0);
		if (!retry)
			dev_err(&ethqos->pdev->dev,
				"Timeout while waiting for DLL lock\n");
	}

	if (ethqos->speed == SPEED_1000)
		ethqos_dll_configure(ethqos);

	ethqos_rgmii_macro_init(ethqos);

	return 0;
}