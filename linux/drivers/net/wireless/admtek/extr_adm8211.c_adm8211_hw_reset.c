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
typedef  int u32 ;
struct ieee80211_hw {struct adm8211_priv* priv; } ;
struct adm8211_priv {scalar_t__ transceiver_type; TYPE_1__* pdev; } ;
struct TYPE_2__ {scalar_t__ revision; } ;

/* Variables and functions */
 int ADM8211_CSR_READ (int /*<<< orphan*/ ) ; 
 int ADM8211_CSR_TEST0_EPRLD ; 
 int /*<<< orphan*/  ADM8211_CSR_WRITE (int /*<<< orphan*/ ,int) ; 
 int ADM8211_PAR_SWR ; 
 scalar_t__ ADM8211_REV_BA ; 
 scalar_t__ ADM8211_REV_CA ; 
 scalar_t__ ADM8211_RFMD2958 ; 
 scalar_t__ ADM8211_RFMD2958_RF3000_CONTROL_POWER ; 
 int /*<<< orphan*/  CSR_TEST0 ; 
 int /*<<< orphan*/  CSR_TEST1 ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FRCTL ; 
 int /*<<< orphan*/  PAR ; 
 int /*<<< orphan*/  adm8211_clear_sram (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static int adm8211_hw_reset(struct ieee80211_hw *dev)
{
	struct adm8211_priv *priv = dev->priv;
	u32 reg, tmp;
	int timeout = 100;

	/* Power-on issue */
	/* TODO: check if this is necessary */
	ADM8211_CSR_WRITE(FRCTL, 0);

	/* Reset the chip */
	tmp = ADM8211_CSR_READ(PAR);
	ADM8211_CSR_WRITE(PAR, ADM8211_PAR_SWR);

	while ((ADM8211_CSR_READ(PAR) & ADM8211_PAR_SWR) && timeout--)
		msleep(50);

	if (timeout <= 0)
		return -ETIMEDOUT;

	ADM8211_CSR_WRITE(PAR, tmp);

	if (priv->pdev->revision == ADM8211_REV_BA &&
	    (priv->transceiver_type == ADM8211_RFMD2958_RF3000_CONTROL_POWER ||
	     priv->transceiver_type == ADM8211_RFMD2958)) {
		reg = ADM8211_CSR_READ(CSR_TEST1);
		reg |= (1 << 4) | (1 << 5);
		ADM8211_CSR_WRITE(CSR_TEST1, reg);
	} else if (priv->pdev->revision == ADM8211_REV_CA) {
		reg = ADM8211_CSR_READ(CSR_TEST1);
		reg &= ~((1 << 4) | (1 << 5));
		ADM8211_CSR_WRITE(CSR_TEST1, reg);
	}

	ADM8211_CSR_WRITE(FRCTL, 0);

	reg = ADM8211_CSR_READ(CSR_TEST0);
	reg |= ADM8211_CSR_TEST0_EPRLD;	/* EEPROM Recall */
	ADM8211_CSR_WRITE(CSR_TEST0, reg);

	adm8211_clear_sram(dev);

	return 0;
}