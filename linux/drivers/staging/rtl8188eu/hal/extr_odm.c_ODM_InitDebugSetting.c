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
struct odm_dm_struct {scalar_t__ DebugComponents; int /*<<< orphan*/  DebugLevel; } ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_DBG_TRACE ; 

void ODM_InitDebugSetting(struct odm_dm_struct *pDM_Odm)
{
	pDM_Odm->DebugLevel = ODM_DBG_TRACE;

	pDM_Odm->DebugComponents = 0;
}