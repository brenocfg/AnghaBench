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
typedef  int u8 ;
struct ksz_device {int features; } ;

/* Variables and functions */
 int NEW_XMII ; 
#define  PORT_GMII_SEL 133 
#define  PORT_GMII_SEL_S1 132 
#define  PORT_MII_SEL 131 
 int PORT_MII_SEL_M ; 
#define  PORT_MII_SEL_S1 130 
#define  PORT_RMII_SEL 129 
#define  PORT_RMII_SEL_S1 128 

__attribute__((used)) static int ksz9477_get_xmii(struct ksz_device *dev, u8 data)
{
	int mode;

	if (dev->features & NEW_XMII) {
		switch (data & PORT_MII_SEL_M) {
		case PORT_MII_SEL:
			mode = 0;
			break;
		case PORT_RMII_SEL:
			mode = 1;
			break;
		case PORT_GMII_SEL:
			mode = 2;
			break;
		default:
			mode = 3;
		}
	} else {
		switch (data & PORT_MII_SEL_M) {
		case PORT_MII_SEL_S1:
			mode = 0;
			break;
		case PORT_RMII_SEL_S1:
			mode = 1;
			break;
		case PORT_GMII_SEL_S1:
			mode = 2;
			break;
		default:
			mode = 3;
		}
	}
	return mode;
}