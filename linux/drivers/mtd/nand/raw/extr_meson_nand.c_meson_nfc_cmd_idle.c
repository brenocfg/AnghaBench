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
struct TYPE_2__ {int chip_select; } ;
struct meson_nfc {scalar_t__ reg_base; TYPE_1__ param; } ;

/* Variables and functions */
 int NFC_CMD_IDLE ; 
 scalar_t__ NFC_REG_CMD ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void meson_nfc_cmd_idle(struct meson_nfc *nfc, u32 time)
{
	writel(nfc->param.chip_select | NFC_CMD_IDLE | (time & 0x3ff),
	       nfc->reg_base + NFC_REG_CMD);
}