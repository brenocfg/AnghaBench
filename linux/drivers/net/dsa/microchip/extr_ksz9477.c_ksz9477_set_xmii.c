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
typedef  int /*<<< orphan*/  u8 ;
struct ksz_device {int features; } ;

/* Variables and functions */
 int NEW_XMII ; 
 int /*<<< orphan*/  PORT_GMII_SEL ; 
 int /*<<< orphan*/  PORT_GMII_SEL_S1 ; 
 int /*<<< orphan*/  PORT_MII_SEL ; 
 int /*<<< orphan*/  PORT_MII_SEL_M ; 
 int /*<<< orphan*/  PORT_MII_SEL_S1 ; 
 int /*<<< orphan*/  PORT_RGMII_SEL ; 
 int /*<<< orphan*/  PORT_RGMII_SEL_S1 ; 
 int /*<<< orphan*/  PORT_RMII_SEL ; 
 int /*<<< orphan*/  PORT_RMII_SEL_S1 ; 

__attribute__((used)) static void ksz9477_set_xmii(struct ksz_device *dev, int mode, u8 *data)
{
	u8 xmii;

	if (dev->features & NEW_XMII) {
		switch (mode) {
		case 0:
			xmii = PORT_MII_SEL;
			break;
		case 1:
			xmii = PORT_RMII_SEL;
			break;
		case 2:
			xmii = PORT_GMII_SEL;
			break;
		default:
			xmii = PORT_RGMII_SEL;
			break;
		}
	} else {
		switch (mode) {
		case 0:
			xmii = PORT_MII_SEL_S1;
			break;
		case 1:
			xmii = PORT_RMII_SEL_S1;
			break;
		case 2:
			xmii = PORT_GMII_SEL_S1;
			break;
		default:
			xmii = PORT_RGMII_SEL_S1;
			break;
		}
	}
	*data &= ~PORT_MII_SEL_M;
	*data |= xmii;
}