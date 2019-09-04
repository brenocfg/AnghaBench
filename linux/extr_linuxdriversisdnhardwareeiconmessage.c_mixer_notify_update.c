#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_11__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  size_t word ;
typedef  int /*<<< orphan*/  dword ;
typedef  scalar_t__ byte ;
struct TYPE_18__ {int* structs; int /*<<< orphan*/  Selector; } ;
struct TYPE_19__ {TYPE_4__ facility_req; } ;
struct TYPE_17__ {int length; int plci; scalar_t__ ncci; int /*<<< orphan*/  controller; scalar_t__ number; int /*<<< orphan*/  command; int /*<<< orphan*/  appl_id; } ;
struct TYPE_22__ {TYPE_5__ info; TYPE_3__ header; } ;
struct TYPE_15__ {int Global_Options; } ;
struct TYPE_21__ {int li_base; int /*<<< orphan*/  Id; TYPE_1__ profile; } ;
struct TYPE_16__ {scalar_t__ Id; } ;
struct TYPE_20__ {int Id; int li_notify_update; int li_bchannel_id; TYPE_7__* adapter; TYPE_11__* appl; int /*<<< orphan*/  nl_remove_id; TYPE_2__ NL; scalar_t__ State; } ;
struct TYPE_14__ {int /*<<< orphan*/  Id; } ;
struct TYPE_13__ {TYPE_6__* plci; } ;
typedef  TYPE_6__ PLCI ;
typedef  TYPE_7__ DIVA_CAPI_ADAPTER ;
typedef  int /*<<< orphan*/  CAPI_MSG_HEADER ;
typedef  TYPE_8__ CAPI_MSG ;

/* Variables and functions */
 scalar_t__ FILE_ ; 
 int GL_LINE_INTERCONNECT_SUPPORTED ; 
 int LI_REQ_SILENT_UPDATE ; 
 int /*<<< orphan*/  SELECTOR_LINE_INTERCONNECT ; 
 int UnMapController (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _FACILITY_R ; 
 size_t _QUEUE_FULL ; 
 size_t api_put (TYPE_11__*,TYPE_8__*) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,...) ; 
 TYPE_10__* li_config_table ; 
 size_t li_total_channels ; 

__attribute__((used)) static void mixer_notify_update(PLCI *plci, byte others)
{
	DIVA_CAPI_ADAPTER *a;
	word i, w;
	PLCI *notify_plci;
	byte msg[sizeof(CAPI_MSG_HEADER) + 6];

	dbug(1, dprintf("[%06lx] %s,%d: mixer_notify_update %d",
			(dword)((plci->Id << 8) | UnMapController(plci->adapter->Id)),
			(char *)(FILE_), __LINE__, others));

	a = plci->adapter;
	if (a->profile.Global_Options & GL_LINE_INTERCONNECT_SUPPORTED)
	{
		if (others)
			plci->li_notify_update = true;
		i = 0;
		do
		{
			notify_plci = NULL;
			if (others)
			{
				while ((i < li_total_channels) && (li_config_table[i].plci == NULL))
					i++;
				if (i < li_total_channels)
					notify_plci = li_config_table[i++].plci;
			}
			else
			{
				if ((plci->li_bchannel_id != 0)
				    && (li_config_table[a->li_base + (plci->li_bchannel_id - 1)].plci == plci))
				{
					notify_plci = plci;
				}
			}
			if ((notify_plci != NULL)
			    && !notify_plci->li_notify_update
			    && (notify_plci->appl != NULL)
			    && (notify_plci->State)
			    && notify_plci->NL.Id && !notify_plci->nl_remove_id)
			{
				notify_plci->li_notify_update = true;
				((CAPI_MSG *) msg)->header.length = 18;
				((CAPI_MSG *) msg)->header.appl_id = notify_plci->appl->Id;
				((CAPI_MSG *) msg)->header.command = _FACILITY_R;
				((CAPI_MSG *) msg)->header.number = 0;
				((CAPI_MSG *) msg)->header.controller = notify_plci->adapter->Id;
				((CAPI_MSG *) msg)->header.plci = notify_plci->Id;
				((CAPI_MSG *) msg)->header.ncci = 0;
				((CAPI_MSG *) msg)->info.facility_req.Selector = SELECTOR_LINE_INTERCONNECT;
				((CAPI_MSG *) msg)->info.facility_req.structs[0] = 3;
				((CAPI_MSG *) msg)->info.facility_req.structs[1] = LI_REQ_SILENT_UPDATE & 0xff;
				((CAPI_MSG *) msg)->info.facility_req.structs[2] = LI_REQ_SILENT_UPDATE >> 8;
				((CAPI_MSG *) msg)->info.facility_req.structs[3] = 0;
				w = api_put(notify_plci->appl, (CAPI_MSG *) msg);
				if (w != _QUEUE_FULL)
				{
					if (w != 0)
					{
						dbug(1, dprintf("[%06lx] %s,%d: Interconnect notify failed %06x %d",
								(dword)((plci->Id << 8) | UnMapController(plci->adapter->Id)),
								(char *)(FILE_), __LINE__,
								(dword)((notify_plci->Id << 8) | UnMapController(notify_plci->adapter->Id)), w));
					}
					notify_plci->li_notify_update = false;
				}
			}
		} while (others && (notify_plci != NULL));
		if (others)
			plci->li_notify_update = false;
	}
}