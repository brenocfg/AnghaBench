#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  scalar_t__ dword ;
struct TYPE_8__ {int MaxNCCI; scalar_t__ Id; } ;
struct TYPE_7__ {int group_optimization_enabled; scalar_t__* CIP_Mask; int max_plci; scalar_t__* Info_Mask; TYPE_1__* plci; } ;
struct TYPE_6__ {int /*<<< orphan*/  group_optimization_mask_table; int /*<<< orphan*/  c_ind_mask_table; TYPE_5__* appl; scalar_t__ Id; } ;
typedef  TYPE_1__ PLCI ;
typedef  TYPE_2__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
 int MAX_APPL ; 
 int MAX_CIP_TYPES ; 
 int /*<<< orphan*/  __clear_bit (int,int /*<<< orphan*/ ) ; 
 TYPE_5__* application ; 
 int /*<<< orphan*/  bitmap_fill (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,...) ; 
 int max_appl ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void group_optimization(DIVA_CAPI_ADAPTER *a, PLCI *plci)
{
	word i, j, k, busy, group_found;
	dword info_mask_group[MAX_CIP_TYPES];
	dword cip_mask_group[MAX_CIP_TYPES];
	word appl_number_group_type[MAX_APPL];
	PLCI *auxplci;

	/* all APPLs within this inc. call are allowed to dial in */
	bitmap_fill(plci->group_optimization_mask_table, MAX_APPL);

	if (!a->group_optimization_enabled)
	{
		dbug(1, dprintf("No group optimization"));
		return;
	}

	dbug(1, dprintf("Group optimization = 0x%x...", a->group_optimization_enabled));

	for (i = 0; i < MAX_CIP_TYPES; i++)
	{
		info_mask_group[i] = 0;
		cip_mask_group[i] = 0;
	}
	for (i = 0; i < MAX_APPL; i++)
	{
		appl_number_group_type[i] = 0;
	}
	for (i = 0; i < max_appl; i++) /* check if any multi instance capable application is present */
	{  /* group_optimization set to 1 means not to optimize multi-instance capable applications (default) */
		if (application[i].Id && (application[i].MaxNCCI) > 1 && (a->CIP_Mask[i]) && (a->group_optimization_enabled == 1))
		{
			dbug(1, dprintf("Multi-Instance capable, no optimization required"));
			return; /* allow good application unfiltered access */
		}
	}
	for (i = 0; i < max_appl; i++) /* Build CIP Groups */
	{
		if (application[i].Id && a->CIP_Mask[i])
		{
			for (k = 0, busy = false; k < a->max_plci; k++)
			{
				if (a->plci[k].Id)
				{
					auxplci = &a->plci[k];
					if (auxplci->appl == &application[i]) {
						/* application has a busy PLCI */
						busy = true;
						dbug(1, dprintf("Appl 0x%x is busy", i + 1));
					} else if (test_bit(i, plci->c_ind_mask_table)) {
						/* application has an incoming call pending */
						busy = true;
						dbug(1, dprintf("Appl 0x%x has inc. call pending", i + 1));
					}
				}
			}

			for (j = 0, group_found = 0; j <= (MAX_CIP_TYPES) && !busy && !group_found; j++)     /* build groups with free applications only */
			{
				if (j == MAX_CIP_TYPES)       /* all groups are in use but group still not found */
				{                           /* the MAX_CIP_TYPES group enables all calls because of field overflow */
					appl_number_group_type[i] = MAX_CIP_TYPES;
					group_found = true;
					dbug(1, dprintf("Field overflow appl 0x%x", i + 1));
				}
				else if ((info_mask_group[j] == a->CIP_Mask[i]) && (cip_mask_group[j] == a->Info_Mask[i]))
				{                                      /* is group already present ?                  */
					appl_number_group_type[i] = j | 0x80;  /* store the group number for each application */
					group_found = true;
					dbug(1, dprintf("Group 0x%x found with appl 0x%x, CIP=0x%lx", appl_number_group_type[i], i + 1, info_mask_group[j]));
				}
				else if (!info_mask_group[j])
				{                                      /* establish a new group                       */
					appl_number_group_type[i] = j | 0x80;  /* store the group number for each application */
					info_mask_group[j] = a->CIP_Mask[i]; /* store the new CIP mask for the new group    */
					cip_mask_group[j] = a->Info_Mask[i]; /* store the new Info_Mask for this new group  */
					group_found = true;
					dbug(1, dprintf("New Group 0x%x established with appl 0x%x, CIP=0x%lx", appl_number_group_type[i], i + 1, info_mask_group[j]));
				}
			}
		}
	}

	for (i = 0; i < max_appl; i++) /* Build group_optimization_mask_table */
	{
		if (appl_number_group_type[i]) /* application is free, has listens and is member of a group */
		{
			if (appl_number_group_type[i] == MAX_CIP_TYPES)
			{
				dbug(1, dprintf("OverflowGroup 0x%x, valid appl = 0x%x, call enabled", appl_number_group_type[i], i + 1));
			}
			else
			{
				dbug(1, dprintf("Group 0x%x, valid appl = 0x%x", appl_number_group_type[i], i + 1));
				for (j = i + 1; j < max_appl; j++)   /* search other group members and mark them as busy        */
				{
					if (appl_number_group_type[i] == appl_number_group_type[j])
					{
						dbug(1, dprintf("Appl 0x%x is member of group 0x%x, no call", j + 1, appl_number_group_type[j]));
						/* disable call on other group members */
						__clear_bit(j, plci->group_optimization_mask_table);
						appl_number_group_type[j] = 0;       /* remove disabled group member from group list */
					}
				}
			}
		}
		else                                                 /* application should not get a call */
		{
			__clear_bit(i, plci->group_optimization_mask_table);
		}
	}

}