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
typedef  int u32 ;
struct TYPE_3__ {int capabilities; int /*<<< orphan*/  core; } ;
struct TYPE_4__ {int id; } ;
struct bcma_bus {TYPE_1__ drv_cc; TYPE_2__ chipinfo; } ;

/* Variables and functions */
 int BCMA_CC_CAP_OTPS ; 
 int BCMA_CC_CAP_OTPS_SHIFT ; 
 int /*<<< orphan*/  BCMA_CC_CHIPSTAT ; 
 int BCMA_CC_CHIPST_4313_OTP_PRESENT ; 
 int BCMA_CC_CHIPST_43228_OTP_PRESENT ; 
 int BCMA_CC_CHIPST_4331_OTP_PRESENT ; 
#define  BCMA_CHIP_ID_BCM4313 137 
#define  BCMA_CHIP_ID_BCM43131 136 
#define  BCMA_CHIP_ID_BCM43142 135 
#define  BCMA_CHIP_ID_BCM43217 134 
#define  BCMA_CHIP_ID_BCM43224 133 
#define  BCMA_CHIP_ID_BCM43225 132 
#define  BCMA_CHIP_ID_BCM43227 131 
#define  BCMA_CHIP_ID_BCM43228 130 
#define  BCMA_CHIP_ID_BCM4331 129 
#define  BCMA_CHIP_ID_BCM43428 128 
 int bcma_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool bcma_sprom_onchip_available(struct bcma_bus *bus)
{
	u32 chip_status;
	u32 otpsize = 0;
	bool present;

	chip_status = bcma_read32(bus->drv_cc.core, BCMA_CC_CHIPSTAT);
	switch (bus->chipinfo.id) {
	case BCMA_CHIP_ID_BCM4313:
		present = chip_status & BCMA_CC_CHIPST_4313_OTP_PRESENT;
		break;

	case BCMA_CHIP_ID_BCM4331:
		present = chip_status & BCMA_CC_CHIPST_4331_OTP_PRESENT;
		break;
	case BCMA_CHIP_ID_BCM43142:
	case BCMA_CHIP_ID_BCM43224:
	case BCMA_CHIP_ID_BCM43225:
		/* for these chips OTP is always available */
		present = true;
		break;
	case BCMA_CHIP_ID_BCM43131:
	case BCMA_CHIP_ID_BCM43217:
	case BCMA_CHIP_ID_BCM43227:
	case BCMA_CHIP_ID_BCM43228:
	case BCMA_CHIP_ID_BCM43428:
		present = chip_status & BCMA_CC_CHIPST_43228_OTP_PRESENT;
		break;
	default:
		present = false;
		break;
	}

	if (present) {
		otpsize = bus->drv_cc.capabilities & BCMA_CC_CAP_OTPS;
		otpsize >>= BCMA_CC_CAP_OTPS_SHIFT;
	}

	return otpsize != 0;
}