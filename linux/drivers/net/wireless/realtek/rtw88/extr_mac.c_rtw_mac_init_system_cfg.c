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
typedef  int u8 ;
typedef  int u32 ;
struct rtw_dev {TYPE_1__* chip; } ;
struct TYPE_2__ {int sys_func_en; } ;

/* Variables and functions */
 int BIT_BOOT_FSPI_EN ; 
 int BIT_DDMA_EN ; 
 int BIT_FSPI_EN ; 
 int BIT_WL_PLATFORM_RST ; 
 int /*<<< orphan*/  REG_CPU_DMEM_CON ; 
 scalar_t__ REG_CR_EXT ; 
 int /*<<< orphan*/  REG_GPIO_MUXCFG ; 
 int /*<<< orphan*/  REG_MCUFW_CTRL ; 
 scalar_t__ REG_SYS_FUNC_EN ; 
 int rtw_read32 (struct rtw_dev*,int /*<<< orphan*/ ) ; 
 int rtw_read8 (struct rtw_dev*,scalar_t__) ; 
 int /*<<< orphan*/  rtw_write32 (struct rtw_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtw_write8 (struct rtw_dev*,scalar_t__,int) ; 

__attribute__((used)) static int rtw_mac_init_system_cfg(struct rtw_dev *rtwdev)
{
	u8 sys_func_en = rtwdev->chip->sys_func_en;
	u8 value8;
	u32 value, tmp;

	value = rtw_read32(rtwdev, REG_CPU_DMEM_CON);
	value |= BIT_WL_PLATFORM_RST | BIT_DDMA_EN;
	rtw_write32(rtwdev, REG_CPU_DMEM_CON, value);

	rtw_write8(rtwdev, REG_SYS_FUNC_EN + 1, sys_func_en);
	value8 = (rtw_read8(rtwdev, REG_CR_EXT + 3) & 0xF0) | 0x0C;
	rtw_write8(rtwdev, REG_CR_EXT + 3, value8);

	/* disable boot-from-flash for driver's DL FW */
	tmp = rtw_read32(rtwdev, REG_MCUFW_CTRL);
	if (tmp & BIT_BOOT_FSPI_EN) {
		rtw_write32(rtwdev, REG_MCUFW_CTRL, tmp & (~BIT_BOOT_FSPI_EN));
		value = rtw_read32(rtwdev, REG_GPIO_MUXCFG) & (~BIT_FSPI_EN);
		rtw_write32(rtwdev, REG_GPIO_MUXCFG, value);
	}

	return 0;
}