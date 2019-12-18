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
struct qcom_ethqos {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BIT (int) ; 
 int SDCC_DLL_CDR_FINE_PHASE ; 
 int SDCC_DLL_CONFIG2_DDR_CAL_EN ; 
 int SDCC_DLL_CONFIG2_DDR_TRAFFIC_INIT_SEL ; 
 int SDCC_DLL_CONFIG2_DDR_TRAFFIC_INIT_SW ; 
 int SDCC_DLL_CONFIG2_DLL_CLOCK_DIS ; 
 int SDCC_DLL_CONFIG2_MCLK_FREQ_CALC ; 
 int SDCC_DLL_CONFIG_CDR_EN ; 
 int SDCC_DLL_CONFIG_CDR_EXT_EN ; 
 unsigned int SDCC_DLL_CONFIG_CK_OUT_EN ; 
 int SDCC_DLL_CONFIG_DLL_EN ; 
 int SDCC_DLL_MCLK_GATING_EN ; 
 int /*<<< orphan*/  SDCC_HC_REG_DLL_CONFIG ; 
 int /*<<< orphan*/  SDCC_HC_REG_DLL_CONFIG2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 unsigned int rgmii_readl (struct qcom_ethqos*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgmii_updatel (struct qcom_ethqos*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ethqos_dll_configure(struct qcom_ethqos *ethqos)
{
	unsigned int val;
	int retry = 1000;

	/* Set CDR_EN */
	rgmii_updatel(ethqos, SDCC_DLL_CONFIG_CDR_EN,
		      SDCC_DLL_CONFIG_CDR_EN, SDCC_HC_REG_DLL_CONFIG);

	/* Set CDR_EXT_EN */
	rgmii_updatel(ethqos, SDCC_DLL_CONFIG_CDR_EXT_EN,
		      SDCC_DLL_CONFIG_CDR_EXT_EN, SDCC_HC_REG_DLL_CONFIG);

	/* Clear CK_OUT_EN */
	rgmii_updatel(ethqos, SDCC_DLL_CONFIG_CK_OUT_EN,
		      0, SDCC_HC_REG_DLL_CONFIG);

	/* Set DLL_EN */
	rgmii_updatel(ethqos, SDCC_DLL_CONFIG_DLL_EN,
		      SDCC_DLL_CONFIG_DLL_EN, SDCC_HC_REG_DLL_CONFIG);

	rgmii_updatel(ethqos, SDCC_DLL_MCLK_GATING_EN,
		      0, SDCC_HC_REG_DLL_CONFIG);

	rgmii_updatel(ethqos, SDCC_DLL_CDR_FINE_PHASE,
		      0, SDCC_HC_REG_DLL_CONFIG);

	/* Wait for CK_OUT_EN clear */
	do {
		val = rgmii_readl(ethqos, SDCC_HC_REG_DLL_CONFIG);
		val &= SDCC_DLL_CONFIG_CK_OUT_EN;
		if (!val)
			break;
		mdelay(1);
		retry--;
	} while (retry > 0);
	if (!retry)
		dev_err(&ethqos->pdev->dev, "Clear CK_OUT_EN timedout\n");

	/* Set CK_OUT_EN */
	rgmii_updatel(ethqos, SDCC_DLL_CONFIG_CK_OUT_EN,
		      SDCC_DLL_CONFIG_CK_OUT_EN, SDCC_HC_REG_DLL_CONFIG);

	/* Wait for CK_OUT_EN set */
	retry = 1000;
	do {
		val = rgmii_readl(ethqos, SDCC_HC_REG_DLL_CONFIG);
		val &= SDCC_DLL_CONFIG_CK_OUT_EN;
		if (val)
			break;
		mdelay(1);
		retry--;
	} while (retry > 0);
	if (!retry)
		dev_err(&ethqos->pdev->dev, "Set CK_OUT_EN timedout\n");

	/* Set DDR_CAL_EN */
	rgmii_updatel(ethqos, SDCC_DLL_CONFIG2_DDR_CAL_EN,
		      SDCC_DLL_CONFIG2_DDR_CAL_EN, SDCC_HC_REG_DLL_CONFIG2);

	rgmii_updatel(ethqos, SDCC_DLL_CONFIG2_DLL_CLOCK_DIS,
		      0, SDCC_HC_REG_DLL_CONFIG2);

	rgmii_updatel(ethqos, SDCC_DLL_CONFIG2_MCLK_FREQ_CALC,
		      0x1A << 10, SDCC_HC_REG_DLL_CONFIG2);

	rgmii_updatel(ethqos, SDCC_DLL_CONFIG2_DDR_TRAFFIC_INIT_SEL,
		      BIT(2), SDCC_HC_REG_DLL_CONFIG2);

	rgmii_updatel(ethqos, SDCC_DLL_CONFIG2_DDR_TRAFFIC_INIT_SW,
		      SDCC_DLL_CONFIG2_DDR_TRAFFIC_INIT_SW,
		      SDCC_HC_REG_DLL_CONFIG2);

	return 0;
}