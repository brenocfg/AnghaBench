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
struct rtsx_pcr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_OCPCTL ; 
 int SD_DETECT_EN ; 
 int SD_OCP_INT_EN ; 
 int /*<<< orphan*/  rtsx_pci_write_register (struct rtsx_pcr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rts5260_disable_ocp(struct rtsx_pcr *pcr)
{
	u8 mask = 0;

	mask = SD_OCP_INT_EN | SD_DETECT_EN;
	rtsx_pci_write_register(pcr, REG_OCPCTL, mask, 0);

}