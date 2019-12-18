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
typedef  int u16 ;
struct encx24j600_priv {scalar_t__ autoneg; scalar_t__ speed; scalar_t__ full_duplex; } ;

/* Variables and functions */
 int ANEN ; 
 scalar_t__ AUTONEG_ENABLE ; 
 int PFULDPX ; 
 int /*<<< orphan*/  PHCON1 ; 
 int RENEG ; 
 int SPD100 ; 
 scalar_t__ SPEED_100 ; 
 int encx24j600_read_phy (struct encx24j600_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encx24j600_write_phy (struct encx24j600_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void encx24j600_update_phcon1(struct encx24j600_priv *priv)
{
	u16 phcon1 = encx24j600_read_phy(priv, PHCON1);

	if (priv->autoneg == AUTONEG_ENABLE) {
		phcon1 |= ANEN | RENEG;
	} else {
		phcon1 &= ~ANEN;
		if (priv->speed == SPEED_100)
			phcon1 |= SPD100;
		else
			phcon1 &= ~SPD100;

		if (priv->full_duplex)
			phcon1 |= PFULDPX;
		else
			phcon1 &= ~PFULDPX;
	}
	encx24j600_write_phy(priv, PHCON1, phcon1);
}