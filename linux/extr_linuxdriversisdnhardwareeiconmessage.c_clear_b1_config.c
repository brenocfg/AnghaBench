#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dword ;
struct TYPE_14__ {TYPE_2__* plci; } ;
struct TYPE_13__ {int Id; int li_bchannel_id; scalar_t__ B1_facilities; scalar_t__ B1_resource; TYPE_1__* adapter; } ;
struct TYPE_12__ {int li_base; int /*<<< orphan*/  Id; } ;
typedef  TYPE_2__ PLCI ;

/* Variables and functions */
 scalar_t__ FILE_ ; 
 int UnMapController (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adjust_b_clear (TYPE_2__*) ; 
 int /*<<< orphan*/  adv_voice_clear_config (TYPE_2__*) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dtmf_parameter_clear_config (TYPE_2__*) ; 
 int /*<<< orphan*/  dtmf_rec_clear_config (TYPE_2__*) ; 
 int /*<<< orphan*/  dtmf_send_clear_config (TYPE_2__*) ; 
 int /*<<< orphan*/  ec_clear_config (TYPE_2__*) ; 
 TYPE_4__* li_config_table ; 
 int /*<<< orphan*/  mixer_clear_config (TYPE_2__*) ; 

__attribute__((used)) static void clear_b1_config(PLCI *plci)
{

	dbug(1, dprintf("[%06lx] %s,%d: clear_b1_config",
			(dword)((plci->Id << 8) | UnMapController(plci->adapter->Id)),
			(char *)(FILE_), __LINE__));

	adv_voice_clear_config(plci);
	adjust_b_clear(plci);

	ec_clear_config(plci);


	dtmf_rec_clear_config(plci);
	dtmf_send_clear_config(plci);
	dtmf_parameter_clear_config(plci);


	if ((plci->li_bchannel_id != 0)
	    && (li_config_table[plci->adapter->li_base + (plci->li_bchannel_id - 1)].plci == plci))
	{
		mixer_clear_config(plci);
		li_config_table[plci->adapter->li_base + (plci->li_bchannel_id - 1)].plci = NULL;
		plci->li_bchannel_id = 0;
	}

	plci->B1_resource = 0;
	plci->B1_facilities = 0;
}