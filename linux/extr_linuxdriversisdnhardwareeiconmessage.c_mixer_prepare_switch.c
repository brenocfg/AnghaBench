#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dword ;
struct TYPE_4__ {scalar_t__ li_plci_b_read_pos; scalar_t__ li_plci_b_req_pos; } ;
typedef  TYPE_1__ PLCI ;

/* Variables and functions */
 scalar_t__ FILE_ ; 
 int /*<<< orphan*/  UnMapId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mixer_indication_coefs_set (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void mixer_prepare_switch(dword Id, PLCI *plci)
{

	dbug(1, dprintf("[%06lx] %s,%d: mixer_prepare_switch",
			UnMapId(Id), (char *)(FILE_), __LINE__));

	do
	{
		mixer_indication_coefs_set(Id, plci);
	} while (plci->li_plci_b_read_pos != plci->li_plci_b_req_pos);
}