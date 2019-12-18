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
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  InitInterrupt8723BSdio (struct adapter*) ; 
 int /*<<< orphan*/  InitSysInterrupt8723BSdio (struct adapter*) ; 
 int /*<<< orphan*/  REG_HIMR ; 
 int /*<<< orphan*/  REG_HISR ; 
 int /*<<< orphan*/  rtw_write32 (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _InitInterrupt(struct adapter *padapter)
{
	/*  HISR - turn all off */
	rtw_write32(padapter, REG_HISR, 0);

	/*  HIMR - turn all off */
	rtw_write32(padapter, REG_HIMR, 0);

	/*  */
	/*  Initialize and enable SDIO Host Interrupt. */
	/*  */
	InitInterrupt8723BSdio(padapter);

	/*  */
	/*  Initialize system Host Interrupt. */
	/*  */
	InitSysInterrupt8723BSdio(padapter);
}