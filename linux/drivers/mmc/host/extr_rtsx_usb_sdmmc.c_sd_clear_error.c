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
struct rtsx_usb_sdmmc {struct rtsx_ucr* ucr; } ;
struct rtsx_ucr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_STOP ; 
 int SD_CLR_ERR ; 
 int SD_STOP ; 
 int /*<<< orphan*/  rtsx_usb_clear_dma_err (struct rtsx_ucr*) ; 
 int /*<<< orphan*/  rtsx_usb_clear_fsm_err (struct rtsx_ucr*) ; 
 int /*<<< orphan*/  rtsx_usb_ep0_write_register (struct rtsx_ucr*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline void sd_clear_error(struct rtsx_usb_sdmmc *host)
{
	struct rtsx_ucr *ucr = host->ucr;
	rtsx_usb_ep0_write_register(ucr, CARD_STOP,
				  SD_STOP | SD_CLR_ERR,
				  SD_STOP | SD_CLR_ERR);

	rtsx_usb_clear_dma_err(ucr);
	rtsx_usb_clear_fsm_err(ucr);
}