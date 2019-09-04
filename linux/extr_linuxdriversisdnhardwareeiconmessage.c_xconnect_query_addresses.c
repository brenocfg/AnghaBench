#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int word ;
typedef  int /*<<< orphan*/  dword ;
typedef  void* byte ;
struct TYPE_11__ {TYPE_2__* plci; } ;
struct TYPE_10__ {void* Req; scalar_t__ ReqCh; TYPE_1__* X; } ;
struct TYPE_9__ {int li_base; int /*<<< orphan*/  (* request ) (TYPE_5__*) ;scalar_t__ li_pri; int /*<<< orphan*/  Id; } ;
struct TYPE_8__ {int Id; int li_bchannel_id; void** internal_req_buffer; TYPE_5__ NL; TYPE_3__* adapter; void* nl_req; TYPE_1__* NData; } ;
struct TYPE_7__ {void** P; int PLength; } ;
typedef  TYPE_2__ PLCI ;
typedef  TYPE_3__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
 scalar_t__ FILE_ ; 
 scalar_t__ N_UDATA ; 
 int /*<<< orphan*/  UDATA_REQUEST_XCONNECT_FROM ; 
 int UnMapController (int /*<<< orphan*/ ) ; 
 int XCONNECT_CHANNEL_PORT_PC ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_6__* li_config_table ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 

__attribute__((used)) static void xconnect_query_addresses(PLCI *plci)
{
	DIVA_CAPI_ADAPTER *a;
	word w, ch;
	byte *p;

	dbug(1, dprintf("[%06lx] %s,%d: xconnect_query_addresses",
			(dword)((plci->Id << 8) | UnMapController(plci->adapter->Id)),
			(char *)(FILE_), __LINE__));

	a = plci->adapter;
	if (a->li_pri && ((plci->li_bchannel_id == 0)
			  || (li_config_table[a->li_base + (plci->li_bchannel_id - 1)].plci != plci)))
	{
		dbug(1, dprintf("[%06x] %s,%d: Channel id wiped out",
				(dword)((plci->Id << 8) | UnMapController(plci->adapter->Id)),
				(char *)(FILE_), __LINE__));
		return;
	}
	p = plci->internal_req_buffer;
	ch = (a->li_pri) ? plci->li_bchannel_id - 1 : 0;
	*(p++) = UDATA_REQUEST_XCONNECT_FROM;
	w = ch;
	*(p++) = (byte) w;
	*(p++) = (byte)(w >> 8);
	w = ch | XCONNECT_CHANNEL_PORT_PC;
	*(p++) = (byte) w;
	*(p++) = (byte)(w >> 8);
	plci->NData[0].P = plci->internal_req_buffer;
	plci->NData[0].PLength = p - plci->internal_req_buffer;
	plci->NL.X = plci->NData;
	plci->NL.ReqCh = 0;
	plci->NL.Req = plci->nl_req = (byte) N_UDATA;
	plci->adapter->request(&plci->NL);
}