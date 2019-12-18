#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pRA_T ;
struct TYPE_4__ {int firstconnect; } ;
struct TYPE_5__ {TYPE_1__ DM_RA_Table; } ;
typedef  TYPE_2__* PDM_ODM_T ;

/* Variables and functions */

void odm_RSSIMonitorInit(PDM_ODM_T pDM_Odm)
{
	pRA_T pRA_Table = &pDM_Odm->DM_RA_Table;

	pRA_Table->firstconnect = false;

}