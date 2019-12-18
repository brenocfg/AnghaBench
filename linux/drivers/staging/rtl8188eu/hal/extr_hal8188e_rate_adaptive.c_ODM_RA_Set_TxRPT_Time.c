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
typedef  int /*<<< orphan*/  u16 ;
struct odm_dm_struct {struct adapter* Adapter; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_TX_RPT_TIME ; 
 int /*<<< orphan*/  usb_write16 (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ODM_RA_Set_TxRPT_Time(struct odm_dm_struct *dm_odm, u16 minRptTime)
{
	struct adapter *adapt = dm_odm->Adapter;

	usb_write16(adapt, REG_TX_RPT_TIME, minRptTime);
}