#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t word ;
typedef  int /*<<< orphan*/  dword ;
struct TYPE_7__ {int* coef_table; scalar_t__* flag_table; scalar_t__ chflags; scalar_t__ channel; scalar_t__ curchnl; TYPE_1__* plci; } ;
struct TYPE_6__ {int li_base; int manufacturer_features; TYPE_1__* AdvSignalPLCI; int /*<<< orphan*/  li_pri; int /*<<< orphan*/  Id; } ;
struct TYPE_5__ {int Id; int li_notify_update; int li_bchannel_id; scalar_t__ tel; TYPE_2__* adapter; scalar_t__ li_plci_b_req_pos; scalar_t__ li_plci_b_read_pos; scalar_t__ li_plci_b_write_pos; } ;
typedef  TYPE_1__ PLCI ;
typedef  TYPE_2__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
 scalar_t__ ADV_VOICE ; 
 scalar_t__ FILE_ ; 
 int LI_COEF_CH_PC_SET ; 
 int LI_COEF_PC_CH_SET ; 
 int MANUFACTURER_FEATURE_SLAVE_CODEC ; 
 int MIXER_IC_CHANNEL_BASE ; 
 int UnMapController (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_4__* li_config_table ; 
 size_t li_total_channels ; 

__attribute__((used)) static void mixer_clear_config(PLCI *plci)
{
	DIVA_CAPI_ADAPTER *a;
	word i, j;

	dbug(1, dprintf("[%06lx] %s,%d: mixer_clear_config",
			(dword)((plci->Id << 8) | UnMapController(plci->adapter->Id)),
			(char *)(FILE_), __LINE__));

	plci->li_notify_update = false;
	plci->li_plci_b_write_pos = 0;
	plci->li_plci_b_read_pos = 0;
	plci->li_plci_b_req_pos = 0;
	a = plci->adapter;
	if ((plci->li_bchannel_id != 0)
	    && (li_config_table[a->li_base + (plci->li_bchannel_id - 1)].plci == plci))
	{
		i = a->li_base + (plci->li_bchannel_id - 1);
		li_config_table[i].curchnl = 0;
		li_config_table[i].channel = 0;
		li_config_table[i].chflags = 0;
		for (j = 0; j < li_total_channels; j++)
		{
			li_config_table[j].flag_table[i] = 0;
			li_config_table[i].flag_table[j] = 0;
			li_config_table[i].coef_table[j] = 0;
			li_config_table[j].coef_table[i] = 0;
		}
		if (!a->li_pri)
		{
			li_config_table[i].coef_table[i] |= LI_COEF_CH_PC_SET | LI_COEF_PC_CH_SET;
			if ((plci->tel == ADV_VOICE) && (plci == a->AdvSignalPLCI))
			{
				i = a->li_base + MIXER_IC_CHANNEL_BASE + (plci->li_bchannel_id - 1);
				li_config_table[i].curchnl = 0;
				li_config_table[i].channel = 0;
				li_config_table[i].chflags = 0;
				for (j = 0; j < li_total_channels; j++)
				{
					li_config_table[i].flag_table[j] = 0;
					li_config_table[j].flag_table[i] = 0;
					li_config_table[i].coef_table[j] = 0;
					li_config_table[j].coef_table[i] = 0;
				}
				if (a->manufacturer_features & MANUFACTURER_FEATURE_SLAVE_CODEC)
				{
					i = a->li_base + MIXER_IC_CHANNEL_BASE + (2 - plci->li_bchannel_id);
					li_config_table[i].curchnl = 0;
					li_config_table[i].channel = 0;
					li_config_table[i].chflags = 0;
					for (j = 0; j < li_total_channels; j++)
					{
						li_config_table[i].flag_table[j] = 0;
						li_config_table[j].flag_table[i] = 0;
						li_config_table[i].coef_table[j] = 0;
						li_config_table[j].coef_table[i] = 0;
					}
				}
			}
		}
	}
}