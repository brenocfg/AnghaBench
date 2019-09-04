#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t word ;
typedef  int /*<<< orphan*/  dword ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_14__ {int curchnl; TYPE_1__* plci; } ;
struct TYPE_13__ {int li_base; int manufacturer_features; TYPE_1__* AdvSignalPLCI; int /*<<< orphan*/  li_pri; } ;
struct TYPE_12__ {size_t internal_command; int li_cmd; int li_channel_bits; int B1_facilities; int* li_plci_b_queue; int li_bchannel_id; scalar_t__ tel; int /*<<< orphan*/  li_plci_b_write_pos; int /*<<< orphan*/  li_plci_b_req_pos; int /*<<< orphan*/  B1_resource; int /*<<< orphan*/  li_plci_b_read_pos; TYPE_2__* adapter; } ;
typedef  TYPE_1__ PLCI ;
typedef  TYPE_2__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
 scalar_t__ ADV_VOICE ; 
 int B1_FACILITY_MIXER ; 
 scalar_t__ FILE_ ; 
 int /*<<< orphan*/  GOOD ; 
 int LI_CHANNEL_INVOLVED ; 
 int LI_PLCI_B_LAST_FLAG ; 
 int /*<<< orphan*/  LI_PLCI_B_QUEUE_ENTRIES ; 
#define  LI_REQ_CONNECT 133 
#define  LI_REQ_DISCONNECT 132 
#define  LI_REQ_SILENT_UPDATE 131 
 int MANUFACTURER_FEATURE_SLAVE_CODEC ; 
#define  MIXER_COMMAND_1 130 
#define  MIXER_COMMAND_2 129 
#define  MIXER_COMMAND_3 128 
 int MIXER_IC_CHANNEL_BASE ; 
 int /*<<< orphan*/  UnMapId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_b1_facilities (TYPE_1__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  adjust_b1_resource (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  adjust_b_process (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,...) ; 
 int get_b1_facilities (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_7__* li_config_table ; 
 int /*<<< orphan*/  mixer_indication_coefs_set (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  xconnect_write_coefs (TYPE_1__*,int) ; 
 int /*<<< orphan*/  xconnect_write_coefs_process (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mixer_command(dword Id, PLCI *plci, byte Rc)
{
	DIVA_CAPI_ADAPTER *a;
	word i, internal_command;

	dbug(1, dprintf("[%06lx] %s,%d: mixer_command %02x %04x %04x",
			UnMapId(Id), (char *)(FILE_), __LINE__, Rc, plci->internal_command,
			plci->li_cmd));

	a = plci->adapter;
	internal_command = plci->internal_command;
	plci->internal_command = 0;
	switch (plci->li_cmd)
	{
	case LI_REQ_CONNECT:
	case LI_REQ_DISCONNECT:
	case LI_REQ_SILENT_UPDATE:
		switch (internal_command)
		{
		default:
			if (plci->li_channel_bits & LI_CHANNEL_INVOLVED)
			{
				adjust_b1_resource(Id, plci, NULL, (word)(plci->B1_facilities |
									  B1_FACILITY_MIXER), MIXER_COMMAND_1);
			}
			/* fall through */
		case MIXER_COMMAND_1:
			if (plci->li_channel_bits & LI_CHANNEL_INVOLVED)
			{
				if (adjust_b_process(Id, plci, Rc) != GOOD)
				{
					dbug(1, dprintf("[%06lx] %s,%d: Load mixer failed",
							UnMapId(Id), (char *)(FILE_), __LINE__));
					break;
				}
				if (plci->internal_command)
					return;
			}
			plci->li_plci_b_req_pos = plci->li_plci_b_write_pos;
			if ((plci->li_channel_bits & LI_CHANNEL_INVOLVED)
			    || ((get_b1_facilities(plci, plci->B1_resource) & B1_FACILITY_MIXER)
				&& (add_b1_facilities(plci, plci->B1_resource, (word)(plci->B1_facilities &
										      ~B1_FACILITY_MIXER)) == plci->B1_resource)))
			{
				xconnect_write_coefs(plci, MIXER_COMMAND_2);
			}
			else
			{
				do
				{
					mixer_indication_coefs_set(Id, plci);
				} while (plci->li_plci_b_read_pos != plci->li_plci_b_req_pos);
			}
			/* fall through */
		case MIXER_COMMAND_2:
			if ((plci->li_channel_bits & LI_CHANNEL_INVOLVED)
			    || ((get_b1_facilities(plci, plci->B1_resource) & B1_FACILITY_MIXER)
				&& (add_b1_facilities(plci, plci->B1_resource, (word)(plci->B1_facilities &
										      ~B1_FACILITY_MIXER)) == plci->B1_resource)))
			{
				if (!xconnect_write_coefs_process(Id, plci, Rc))
				{
					dbug(1, dprintf("[%06lx] %s,%d: Write mixer coefs failed",
							UnMapId(Id), (char *)(FILE_), __LINE__));
					if (plci->li_plci_b_write_pos != plci->li_plci_b_req_pos)
					{
						do
						{
							plci->li_plci_b_write_pos = (plci->li_plci_b_write_pos == 0) ?
								LI_PLCI_B_QUEUE_ENTRIES - 1 : plci->li_plci_b_write_pos - 1;
							i = (plci->li_plci_b_write_pos == 0) ?
								LI_PLCI_B_QUEUE_ENTRIES - 1 : plci->li_plci_b_write_pos - 1;
						} while ((plci->li_plci_b_write_pos != plci->li_plci_b_req_pos)
							 && !(plci->li_plci_b_queue[i] & LI_PLCI_B_LAST_FLAG));
					}
					break;
				}
				if (plci->internal_command)
					return;
			}
			if (!(plci->li_channel_bits & LI_CHANNEL_INVOLVED))
			{
				adjust_b1_resource(Id, plci, NULL, (word)(plci->B1_facilities &
									  ~B1_FACILITY_MIXER), MIXER_COMMAND_3);
			}
			/* fall through */
		case MIXER_COMMAND_3:
			if (!(plci->li_channel_bits & LI_CHANNEL_INVOLVED))
			{
				if (adjust_b_process(Id, plci, Rc) != GOOD)
				{
					dbug(1, dprintf("[%06lx] %s,%d: Unload mixer failed",
							UnMapId(Id), (char *)(FILE_), __LINE__));
					break;
				}
				if (plci->internal_command)
					return;
			}
			break;
		}
		break;
	}
	if ((plci->li_bchannel_id == 0)
	    || (li_config_table[a->li_base + (plci->li_bchannel_id - 1)].plci != plci))
	{
		dbug(1, dprintf("[%06x] %s,%d: Channel id wiped out %d",
				UnMapId(Id), (char *)(FILE_), __LINE__, (int)(plci->li_bchannel_id)));
	}
	else
	{
		i = a->li_base + (plci->li_bchannel_id - 1);
		li_config_table[i].curchnl = plci->li_channel_bits;
		if (!a->li_pri && (plci->tel == ADV_VOICE) && (plci == a->AdvSignalPLCI))
		{
			i = a->li_base + MIXER_IC_CHANNEL_BASE + (plci->li_bchannel_id - 1);
			li_config_table[i].curchnl = plci->li_channel_bits;
			if (a->manufacturer_features & MANUFACTURER_FEATURE_SLAVE_CODEC)
			{
				i = a->li_base + MIXER_IC_CHANNEL_BASE + (2 - plci->li_bchannel_id);
				li_config_table[i].curchnl = plci->li_channel_bits;
			}
		}
	}
}