#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
typedef  size_t word ;
typedef  int dword ;
struct TYPE_13__ {int Global_Options; } ;
struct TYPE_17__ {int li_base; TYPE_1__ profile; int /*<<< orphan*/  Id; } ;
struct TYPE_15__ {scalar_t__ Id; } ;
struct TYPE_16__ {int Id; int li_bchannel_id; int /*<<< orphan*/  nl_remove_id; TYPE_3__ NL; scalar_t__ State; TYPE_2__* appl; TYPE_5__* adapter; } ;
struct TYPE_14__ {int appl_flags; } ;
struct TYPE_12__ {int curchnl; int channel; int* flag_table; TYPE_4__* plci; } ;
typedef  TYPE_4__ PLCI ;
typedef  TYPE_5__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
 int APPL_FLAG_OLD_LI_SPEC ; 
 scalar_t__ FILE_ ; 
 int GL_LINE_INTERCONNECT_SUPPORTED ; 
 int LI_CHANNEL_INVOLVED ; 
 int LI_FLAG_INTERCONNECT ; 
 int UnMapController (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int,char*,int) ; 
 TYPE_11__* li_config_table ; 
 size_t li_total_channels ; 
 int /*<<< orphan*/  mixer_calculate_coefs (TYPE_5__*) ; 
 int /*<<< orphan*/  mixer_clear_config (TYPE_4__*) ; 
 int /*<<< orphan*/  mixer_notify_source_removed (TYPE_4__*,int) ; 
 int /*<<< orphan*/  mixer_notify_update (TYPE_4__*,int) ; 

__attribute__((used)) static void mixer_remove(PLCI *plci)
{
	DIVA_CAPI_ADAPTER *a;
	PLCI *notify_plci;
	dword plci_b_id;
	word i, j;

	dbug(1, dprintf("[%06lx] %s,%d: mixer_remove",
			(dword)((plci->Id << 8) | UnMapController(plci->adapter->Id)),
			(char *)(FILE_), __LINE__));

	a = plci->adapter;
	plci_b_id = (plci->Id << 8) | UnMapController(plci->adapter->Id);
	if (a->profile.Global_Options & GL_LINE_INTERCONNECT_SUPPORTED)
	{
		if ((plci->li_bchannel_id != 0)
		    && (li_config_table[a->li_base + (plci->li_bchannel_id - 1)].plci == plci))
		{
			i = a->li_base + (plci->li_bchannel_id - 1);
			if ((li_config_table[i].curchnl | li_config_table[i].channel) & LI_CHANNEL_INVOLVED)
			{
				for (j = 0; j < li_total_channels; j++)
				{
					if ((li_config_table[i].flag_table[j] & LI_FLAG_INTERCONNECT)
					    || (li_config_table[j].flag_table[i] & LI_FLAG_INTERCONNECT))
					{
						notify_plci = li_config_table[j].plci;
						if ((notify_plci != NULL)
						    && (notify_plci != plci)
						    && (notify_plci->appl != NULL)
						    && !(notify_plci->appl->appl_flags & APPL_FLAG_OLD_LI_SPEC)
						    && (notify_plci->State)
						    && notify_plci->NL.Id && !notify_plci->nl_remove_id)
						{
							mixer_notify_source_removed(notify_plci, plci_b_id);
						}
					}
				}
				mixer_clear_config(plci);
				mixer_calculate_coefs(a);
				mixer_notify_update(plci, true);
			}
			li_config_table[i].plci = NULL;
			plci->li_bchannel_id = 0;
		}
	}
}