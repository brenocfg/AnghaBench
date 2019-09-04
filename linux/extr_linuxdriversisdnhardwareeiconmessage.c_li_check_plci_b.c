#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ word ;
typedef  int dword ;
typedef  int byte ;
struct TYPE_14__ {int max_plci; TYPE_3__* plci; int /*<<< orphan*/ * request; } ;
struct TYPE_13__ {TYPE_3__* plci; } ;
struct TYPE_10__ {int /*<<< orphan*/  Id; } ;
struct TYPE_12__ {scalar_t__ li_plci_b_read_pos; int li_bchannel_id; int B1_resource; int B1_facilities; TYPE_2__* adapter; scalar_t__ nl_remove_id; TYPE_1__ NL; int /*<<< orphan*/  State; } ;
struct TYPE_11__ {int li_base; int manufacturer_features; int /*<<< orphan*/  Id; } ;
typedef  TYPE_3__ PLCI ;

/* Variables and functions */
 int B1_FACILITY_MIXER ; 
 int EXT_CONTROLLER ; 
 scalar_t__ FILE_ ; 
 scalar_t__ LI_PLCI_B_QUEUE_ENTRIES ; 
 int MANUFACTURER_FEATURE_XCONNECT ; 
 int MapController (int) ; 
 int /*<<< orphan*/  PUT_WORD (int*,int /*<<< orphan*/ ) ; 
 int UnMapController (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnMapId (int) ; 
 int /*<<< orphan*/  _REQUEST_NOT_ALLOWED_IN_THIS_STATE ; 
 int /*<<< orphan*/  _WRONG_IDENTIFIER ; 
 TYPE_9__* adapter ; 
 int /*<<< orphan*/  add_b1_facilities (TYPE_3__*,int,scalar_t__) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,...) ; 
 int get_b1_facilities (TYPE_3__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* li_config_table ; 
 int max_adapter ; 

__attribute__((used)) static PLCI *li_check_plci_b(dword Id, PLCI *plci,
			     dword plci_b_id, word plci_b_write_pos, byte *p_result)
{
	byte ctlr_b;
	PLCI *plci_b;

	if (((plci->li_plci_b_read_pos > plci_b_write_pos) ? plci->li_plci_b_read_pos :
	     LI_PLCI_B_QUEUE_ENTRIES + plci->li_plci_b_read_pos) - plci_b_write_pos - 1 < 2)
	{
		dbug(1, dprintf("[%06lx] %s,%d: LI request overrun",
				UnMapId(Id), (char *)(FILE_), __LINE__));
		PUT_WORD(p_result, _REQUEST_NOT_ALLOWED_IN_THIS_STATE);
		return (NULL);
	}
	ctlr_b = 0;
	if ((plci_b_id & 0x7f) != 0)
	{
		ctlr_b = MapController((byte)(plci_b_id & 0x7f));
		if ((ctlr_b > max_adapter) || ((ctlr_b != 0) && (adapter[ctlr_b - 1].request == NULL)))
			ctlr_b = 0;
	}
	if ((ctlr_b == 0)
	    || (((plci_b_id >> 8) & 0xff) == 0)
	    || (((plci_b_id >> 8) & 0xff) > adapter[ctlr_b - 1].max_plci))
	{
		dbug(1, dprintf("[%06lx] %s,%d: LI invalid second PLCI %08lx",
				UnMapId(Id), (char *)(FILE_), __LINE__, plci_b_id));
		PUT_WORD(p_result, _WRONG_IDENTIFIER);
		return (NULL);
	}
	plci_b = &(adapter[ctlr_b - 1].plci[((plci_b_id >> 8) & 0xff) - 1]);
	if (!plci_b->State
	    || !plci_b->NL.Id || plci_b->nl_remove_id
	    || (plci_b->li_bchannel_id == 0))
	{
		dbug(1, dprintf("[%06lx] %s,%d: LI peer in wrong state %08lx",
				UnMapId(Id), (char *)(FILE_), __LINE__, plci_b_id));
		PUT_WORD(p_result, _REQUEST_NOT_ALLOWED_IN_THIS_STATE);
		return (NULL);
	}
	li_config_table[plci_b->adapter->li_base + (plci_b->li_bchannel_id - 1)].plci = plci_b;
	if (((byte)(plci_b_id & ~EXT_CONTROLLER)) !=
	    ((byte)(UnMapController(plci->adapter->Id) & ~EXT_CONTROLLER))
	    && (!(plci->adapter->manufacturer_features & MANUFACTURER_FEATURE_XCONNECT)
		|| !(plci_b->adapter->manufacturer_features & MANUFACTURER_FEATURE_XCONNECT)))
	{
		dbug(1, dprintf("[%06lx] %s,%d: LI not on same ctrl %08lx",
				UnMapId(Id), (char *)(FILE_), __LINE__, plci_b_id));
		PUT_WORD(p_result, _WRONG_IDENTIFIER);
		return (NULL);
	}
	if (!(get_b1_facilities(plci_b, add_b1_facilities(plci_b, plci_b->B1_resource,
							  (word)(plci_b->B1_facilities | B1_FACILITY_MIXER))) & B1_FACILITY_MIXER))
	{
		dbug(1, dprintf("[%06lx] %s,%d: Interconnect peer cannot mix %d",
				UnMapId(Id), (char *)(FILE_), __LINE__, plci_b->B1_resource));
		PUT_WORD(p_result, _REQUEST_NOT_ALLOWED_IN_THIS_STATE);
		return (NULL);
	}
	return (plci_b);
}