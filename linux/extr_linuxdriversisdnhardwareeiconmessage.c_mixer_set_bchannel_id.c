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
typedef  int /*<<< orphan*/  dword ;
typedef  int byte ;
struct TYPE_8__ {TYPE_1__* plci; } ;
struct TYPE_7__ {int li_base; int /*<<< orphan*/  Id; TYPE_1__* AdvSignalPLCI; scalar_t__ li_pri; } ;
struct TYPE_6__ {int li_bchannel_id; scalar_t__ tel; int Id; TYPE_2__* adapter; } ;
typedef  TYPE_1__ PLCI ;
typedef  TYPE_2__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
 scalar_t__ ADV_VOICE ; 
 scalar_t__ FILE_ ; 
 int UnMapController (int /*<<< orphan*/ ) ; 
 int chi_to_channel (int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,int,...) ; 
 TYPE_5__* li_config_table ; 
 int /*<<< orphan*/  mixer_clear_config (TYPE_1__*) ; 

__attribute__((used)) static void mixer_set_bchannel_id(PLCI *plci, byte *chi)
{
	DIVA_CAPI_ADAPTER *a;
	PLCI *splci;
	byte ch, old_id;

	a = plci->adapter;
	old_id = plci->li_bchannel_id;
	ch = chi_to_channel(chi, NULL);
	if (!(ch & 0x80))
	{
		if (a->li_pri)
		{
			if ((old_id != 0) && (li_config_table[a->li_base + (old_id - 1)].plci == plci))
				li_config_table[a->li_base + (old_id - 1)].plci = NULL;
			plci->li_bchannel_id = (ch & 0x1f) + 1;
			if (li_config_table[a->li_base + (plci->li_bchannel_id - 1)].plci == NULL)
				li_config_table[a->li_base + (plci->li_bchannel_id - 1)].plci = plci;
		}
		else
		{
			if (((ch & 0x1f) == 1) || ((ch & 0x1f) == 2))
			{
				if ((old_id != 0) && (li_config_table[a->li_base + (old_id - 1)].plci == plci))
					li_config_table[a->li_base + (old_id - 1)].plci = NULL;
				plci->li_bchannel_id = ch & 0x1f;
				if ((a->AdvSignalPLCI != NULL) && (a->AdvSignalPLCI != plci) && (a->AdvSignalPLCI->tel == ADV_VOICE))
				{
					splci = a->AdvSignalPLCI;
					if (li_config_table[a->li_base + (2 - plci->li_bchannel_id)].plci == NULL)
					{
						if ((splci->li_bchannel_id != 0)
						    && (li_config_table[a->li_base + (splci->li_bchannel_id - 1)].plci == splci))
						{
							li_config_table[a->li_base + (splci->li_bchannel_id - 1)].plci = NULL;
						}
						splci->li_bchannel_id = 3 - plci->li_bchannel_id;
						li_config_table[a->li_base + (2 - plci->li_bchannel_id)].plci = splci;
						dbug(1, dprintf("[%06lx] %s,%d: adv_voice_set_bchannel_id %d",
								(dword)((splci->Id << 8) | UnMapController(splci->adapter->Id)),
								(char *)(FILE_), __LINE__, splci->li_bchannel_id));
					}
				}
				if (li_config_table[a->li_base + (plci->li_bchannel_id - 1)].plci == NULL)
					li_config_table[a->li_base + (plci->li_bchannel_id - 1)].plci = plci;
			}
		}
	}
	if ((old_id == 0) && (plci->li_bchannel_id != 0)
	    && (li_config_table[a->li_base + (plci->li_bchannel_id - 1)].plci == plci))
	{
		mixer_clear_config(plci);
	}
	dbug(1, dprintf("[%06lx] %s,%d: mixer_set_bchannel_id %02x %d",
			(dword)((plci->Id << 8) | UnMapController(plci->adapter->Id)),
			(char *)(FILE_), __LINE__, ch, plci->li_bchannel_id));
}