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
struct zd_ioreq32 {int member_1; int /*<<< orphan*/  const member_0; } ;
struct zd_chip {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct zd_ioreq32 const*) ; 
#define  CR_ACK_TIMEOUT_EXT 148 
#define  CR_ACK_TIME_80211 147 
#define  CR_ADDA_MBIAS_WARMTIME 146 
#define  CR_ADDA_PWR_DWN 145 
#define  CR_AFTER_PNP 144 
#define  CR_BCN_PLCP_CFG 143 
#define  CR_CAM_MODE 142 
#define  CR_GROUP_HASH_P1 141 
#define  CR_GROUP_HASH_P2 140 
#define  CR_IFS_VALUE 139 
#define  CR_PHY_DELAY 138 
#define  CR_PS_CTRL 137 
#define  CR_REG1 136 
#define  CR_RTS_CTS_RATE 135 
#define  CR_RX_FILTER 134 
#define  CR_RX_PE_DELAY 133 
#define  CR_SNIFFER_ON 132 
#define  CR_WEP_PROTECT 131 
#define  IFS_VALUE_DEFAULT 130 
#define  MODE_AP_WDS 129 
#define  STA_RX_FILTER 128 
 int /*<<< orphan*/  ZD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int zd1211_hw_init_hmac (struct zd_chip*) ; 
 int zd1211b_hw_init_hmac (struct zd_chip*) ; 
 scalar_t__ zd_chip_is_zd1211b (struct zd_chip*) ; 
 int zd_iowrite32a_locked (struct zd_chip*,struct zd_ioreq32 const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hw_init_hmac(struct zd_chip *chip)
{
	int r;
	static const struct zd_ioreq32 ioreqs[] = {
		{ CR_ACK_TIMEOUT_EXT,		0x20 },
		{ CR_ADDA_MBIAS_WARMTIME,	0x30000808 },
		{ CR_SNIFFER_ON,		0 },
		{ CR_RX_FILTER,			STA_RX_FILTER },
		{ CR_GROUP_HASH_P1,		0x00 },
		{ CR_GROUP_HASH_P2,		0x80000000 },
		{ CR_REG1,			0xa4 },
		{ CR_ADDA_PWR_DWN,		0x7f },
		{ CR_BCN_PLCP_CFG,		0x00f00401 },
		{ CR_PHY_DELAY,			0x00 },
		{ CR_ACK_TIMEOUT_EXT,		0x80 },
		{ CR_ADDA_PWR_DWN,		0x00 },
		{ CR_ACK_TIME_80211,		0x100 },
		{ CR_RX_PE_DELAY,		0x70 },
		{ CR_PS_CTRL,			0x10000000 },
		{ CR_RTS_CTS_RATE,		0x02030203 },
		{ CR_AFTER_PNP,			0x1 },
		{ CR_WEP_PROTECT,		0x114 },
		{ CR_IFS_VALUE,			IFS_VALUE_DEFAULT },
		{ CR_CAM_MODE,			MODE_AP_WDS},
	};

	ZD_ASSERT(mutex_is_locked(&chip->mutex));
	r = zd_iowrite32a_locked(chip, ioreqs, ARRAY_SIZE(ioreqs));
	if (r)
		return r;

	return zd_chip_is_zd1211b(chip) ?
		zd1211b_hw_init_hmac(chip) : zd1211_hw_init_hmac(chip);
}