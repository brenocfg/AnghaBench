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
struct vnt_private {int bRadioOff; int byRFType; int /*<<< orphan*/  PortOffset; int /*<<< orphan*/  byLocalID; } ;

/* Variables and functions */
 int /*<<< orphan*/  BBvSetDeepSleep (struct vnt_private*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOSTCR_RXON ; 
 int /*<<< orphan*/  LED_ACTSET ; 
 int /*<<< orphan*/  MAC_REG_GPIOCTL0 ; 
 int /*<<< orphan*/  MAC_REG_HOSTCR ; 
 int /*<<< orphan*/  MAC_REG_SOFTPWRCTL ; 
 int /*<<< orphan*/  MACvRegBitsOff (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvRegBitsOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvWordRegBitsOff (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACvWordRegBitsOn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  RF_AIROHA 131 
#define  RF_AIROHA7230 130 
#define  RF_AL2230S 129 
#define  RF_RFMD2959 128 
 int /*<<< orphan*/  SOFTPWRCTL_SWPE1 ; 
 int /*<<< orphan*/  SOFTPWRCTL_SWPE2 ; 
 int /*<<< orphan*/  SOFTPWRCTL_SWPE3 ; 
 int /*<<< orphan*/  SOFTPWRCTL_TXPEINV ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

void CARDbRadioPowerOff(struct vnt_private *priv)
{
	if (priv->bRadioOff)
		return;

	switch (priv->byRFType) {
	case RF_RFMD2959:
		MACvWordRegBitsOff(priv->PortOffset, MAC_REG_SOFTPWRCTL,
				   SOFTPWRCTL_TXPEINV);
		MACvWordRegBitsOn(priv->PortOffset, MAC_REG_SOFTPWRCTL,
				  SOFTPWRCTL_SWPE1);
		break;

	case RF_AIROHA:
	case RF_AL2230S:
	case RF_AIROHA7230:
		MACvWordRegBitsOff(priv->PortOffset, MAC_REG_SOFTPWRCTL,
				   SOFTPWRCTL_SWPE2);
		MACvWordRegBitsOff(priv->PortOffset, MAC_REG_SOFTPWRCTL,
				   SOFTPWRCTL_SWPE3);
		break;
	}

	MACvRegBitsOff(priv->PortOffset, MAC_REG_HOSTCR, HOSTCR_RXON);

	BBvSetDeepSleep(priv, priv->byLocalID);

	priv->bRadioOff = true;
	pr_debug("chester power off\n");
	MACvRegBitsOn(priv->PortOffset, MAC_REG_GPIOCTL0,
		      LED_ACTSET);  /* LED issue */
}