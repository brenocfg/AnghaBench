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
struct rtsx_usb_sdmmc {int /*<<< orphan*/  ucr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SD_CFG1 ; 
 int /*<<< orphan*/  SD_CLK_DIVIDE_128 ; 
 int /*<<< orphan*/  SD_CLK_DIVIDE_MASK ; 
 int /*<<< orphan*/  rtsx_usb_write_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void sd_enable_initial_mode(struct rtsx_usb_sdmmc *host)
{
	rtsx_usb_write_register(host->ucr, SD_CFG1,
			SD_CLK_DIVIDE_MASK, SD_CLK_DIVIDE_128);
}