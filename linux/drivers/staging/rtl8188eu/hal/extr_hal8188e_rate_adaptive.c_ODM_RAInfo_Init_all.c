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
typedef  scalar_t__ u8 ;
struct odm_dm_struct {scalar_t__ CurrminRptTime; } ;

/* Variables and functions */
 scalar_t__ ODM_ASSOCIATE_ENTRY_NUM ; 
 int /*<<< orphan*/  ODM_COMP_RATE_ADAPTIVE ; 
 int /*<<< orphan*/  ODM_DBG_LOUD ; 
 int /*<<< orphan*/  ODM_RAInfo_Init (struct odm_dm_struct*,scalar_t__) ; 
 int /*<<< orphan*/  ODM_RT_TRACE (struct odm_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

int ODM_RAInfo_Init_all(struct odm_dm_struct *dm_odm)
{
	u8 macid = 0;

	ODM_RT_TRACE(dm_odm, ODM_COMP_RATE_ADAPTIVE, ODM_DBG_LOUD, ("=====>\n"));
	dm_odm->CurrminRptTime = 0;

	for (macid = 0; macid < ODM_ASSOCIATE_ENTRY_NUM; macid++)
		ODM_RAInfo_Init(dm_odm, macid);

	return 0;
}