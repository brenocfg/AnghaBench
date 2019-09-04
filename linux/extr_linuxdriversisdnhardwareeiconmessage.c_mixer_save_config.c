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
typedef  int /*<<< orphan*/  byte ;
struct TYPE_7__ {int* coef_table; TYPE_1__* plci; } ;
struct TYPE_6__ {int li_base; int /*<<< orphan*/  li_pri; } ;
struct TYPE_5__ {int li_bchannel_id; TYPE_2__* adapter; int /*<<< orphan*/  adjust_b_state; } ;
typedef  TYPE_1__ PLCI ;
typedef  TYPE_2__ DIVA_CAPI_ADAPTER ;

/* Variables and functions */
 scalar_t__ FILE_ ; 
 size_t GOOD ; 
 int LI_COEF_CH_PC_SET ; 
 int LI_COEF_PC_CH_SET ; 
 int /*<<< orphan*/  UnMapId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbug (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* li_config_table ; 
 size_t li_total_channels ; 

__attribute__((used)) static word mixer_save_config(dword Id, PLCI *plci, byte Rc)
{
	DIVA_CAPI_ADAPTER *a;
	word i, j;

	dbug(1, dprintf("[%06lx] %s,%d: mixer_save_config %02x %d",
			UnMapId(Id), (char *)(FILE_), __LINE__, Rc, plci->adjust_b_state));

	a = plci->adapter;
	if ((plci->li_bchannel_id != 0)
	    && (li_config_table[a->li_base + (plci->li_bchannel_id - 1)].plci == plci))
	{
		i = a->li_base + (plci->li_bchannel_id - 1);
		for (j = 0; j < li_total_channels; j++)
		{
			li_config_table[i].coef_table[j] &= 0xf;
			li_config_table[j].coef_table[i] &= 0xf;
		}
		if (!a->li_pri)
			li_config_table[i].coef_table[i] |= LI_COEF_CH_PC_SET | LI_COEF_PC_CH_SET;
	}
	return (GOOD);
}