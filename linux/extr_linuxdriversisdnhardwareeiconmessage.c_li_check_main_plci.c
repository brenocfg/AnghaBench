#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  word ;
typedef  int /*<<< orphan*/  dword ;
struct TYPE_9__ {TYPE_3__* plci; } ;
struct TYPE_7__ {int /*<<< orphan*/  Id; } ;
struct TYPE_8__ {int li_bchannel_id; TYPE_1__* adapter; scalar_t__ nl_remove_id; TYPE_2__ NL; int /*<<< orphan*/  State; } ;
struct TYPE_6__ {int li_base; } ;
typedef  TYPE_3__ PLCI ;

/* Variables and functions */
 scalar_t__ FILE_ ; 
 int /*<<< orphan*/  GOOD ; 
 int /*<<< orphan*/  UnMapId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _WRONG_IDENTIFIER ; 
 int /*<<< orphan*/  _WRONG_STATE ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_4__* li_config_table ; 

__attribute__((used)) static word li_check_main_plci(dword Id, PLCI *plci)
{
	if (plci == NULL)
	{
		dbug(1, dprintf("[%06lx] %s,%d: Wrong PLCI",
				UnMapId(Id), (char *)(FILE_), __LINE__));
		return (_WRONG_IDENTIFIER);
	}
	if (!plci->State
	    || !plci->NL.Id || plci->nl_remove_id
	    || (plci->li_bchannel_id == 0))
	{
		dbug(1, dprintf("[%06lx] %s,%d: Wrong state",
				UnMapId(Id), (char *)(FILE_), __LINE__));
		return (_WRONG_STATE);
	}
	li_config_table[plci->adapter->li_base + (plci->li_bchannel_id - 1)].plci = plci;
	return (GOOD);
}