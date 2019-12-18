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
typedef  size_t u8 ;
struct odm_dm_struct {TYPE_1__* RAInfo; } ;
struct TYPE_2__ {size_t PTStage; } ;

/* Variables and functions */
 size_t ASSOCIATE_ENTRY_NUM ; 
 int /*<<< orphan*/  ODM_COMP_RATE_ADAPTIVE ; 
 int /*<<< orphan*/  ODM_DBG_TRACE ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct odm_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

u8 ODM_RA_GetHwPwrStatus_8188E(struct odm_dm_struct *dm_odm, u8 macid)
{
	u8 PTStage = 5;

	if ((!dm_odm) || (macid >= ASSOCIATE_ENTRY_NUM))
		return 0;
	PTStage = dm_odm->RAInfo[macid].PTStage;
	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_TRACE,
		     ("macid =%d PTStage = 0x%x\n", macid, PTStage));
	return PTStage;
}