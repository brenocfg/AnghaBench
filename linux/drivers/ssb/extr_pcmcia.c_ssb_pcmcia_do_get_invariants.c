#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_5__ {int TupleDataLen; int* TupleData; } ;
typedef  TYPE_2__ tuple_t ;
struct TYPE_4__ {int a0; int a1; int a2; int a3; } ;
struct ssb_sprom {int board_rev; int pa0b0; int pa0b1; int pa0b2; int itssi_a; int itssi_bg; int maxpwr_a; int maxpwr_bg; int country_code; int ant_available_a; int ant_available_bg; int boardflags_lo; int gpio0; int gpio1; int gpio2; int gpio3; TYPE_1__ antenna_gain; } ;
struct ssb_boardinfo {int vendor; } ;
struct ssb_init_invariants {struct ssb_boardinfo boardinfo; struct ssb_sprom sprom; } ;
struct pcmcia_device {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GOTO_ERROR_ON (int,char*) ; 
#define  SSB_PCMCIA_CIS_ANTENNA 136 
#define  SSB_PCMCIA_CIS_ANTGAIN 135 
#define  SSB_PCMCIA_CIS_BFLAGS 134 
#define  SSB_PCMCIA_CIS_BOARDREV 133 
#define  SSB_PCMCIA_CIS_CCODE 132 
#define  SSB_PCMCIA_CIS_ID 131 
#define  SSB_PCMCIA_CIS_LEDS 130 
#define  SSB_PCMCIA_CIS_OEMNAME 129 
#define  SSB_PCMCIA_CIS_PA 128 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 

__attribute__((used)) static int ssb_pcmcia_do_get_invariants(struct pcmcia_device *p_dev,
					tuple_t *tuple,
					void *priv)
{
	struct ssb_init_invariants *iv = priv;
	struct ssb_sprom *sprom = &iv->sprom;
	struct ssb_boardinfo *bi = &iv->boardinfo;
	const char *error_description;

	GOTO_ERROR_ON(tuple->TupleDataLen < 1, "VEN tpl < 1");
	switch (tuple->TupleData[0]) {
	case SSB_PCMCIA_CIS_ID:
		GOTO_ERROR_ON((tuple->TupleDataLen != 5) &&
			      (tuple->TupleDataLen != 7),
			      "id tpl size");
		bi->vendor = tuple->TupleData[1] |
			((u16)tuple->TupleData[2] << 8);
		break;
	case SSB_PCMCIA_CIS_BOARDREV:
		GOTO_ERROR_ON(tuple->TupleDataLen != 2,
			"boardrev tpl size");
		sprom->board_rev = tuple->TupleData[1];
		break;
	case SSB_PCMCIA_CIS_PA:
		GOTO_ERROR_ON((tuple->TupleDataLen != 9) &&
			(tuple->TupleDataLen != 10),
			"pa tpl size");
		sprom->pa0b0 = tuple->TupleData[1] |
			((u16)tuple->TupleData[2] << 8);
		sprom->pa0b1 = tuple->TupleData[3] |
			((u16)tuple->TupleData[4] << 8);
		sprom->pa0b2 = tuple->TupleData[5] |
			((u16)tuple->TupleData[6] << 8);
		sprom->itssi_a = tuple->TupleData[7];
		sprom->itssi_bg = tuple->TupleData[7];
		sprom->maxpwr_a = tuple->TupleData[8];
		sprom->maxpwr_bg = tuple->TupleData[8];
		break;
	case SSB_PCMCIA_CIS_OEMNAME:
		/* We ignore this. */
		break;
	case SSB_PCMCIA_CIS_CCODE:
		GOTO_ERROR_ON(tuple->TupleDataLen != 2,
			"ccode tpl size");
		sprom->country_code = tuple->TupleData[1];
		break;
	case SSB_PCMCIA_CIS_ANTENNA:
		GOTO_ERROR_ON(tuple->TupleDataLen != 2,
			"ant tpl size");
		sprom->ant_available_a = tuple->TupleData[1];
		sprom->ant_available_bg = tuple->TupleData[1];
		break;
	case SSB_PCMCIA_CIS_ANTGAIN:
		GOTO_ERROR_ON(tuple->TupleDataLen != 2,
			"antg tpl size");
		sprom->antenna_gain.a0 = tuple->TupleData[1];
		sprom->antenna_gain.a1 = tuple->TupleData[1];
		sprom->antenna_gain.a2 = tuple->TupleData[1];
		sprom->antenna_gain.a3 = tuple->TupleData[1];
		break;
	case SSB_PCMCIA_CIS_BFLAGS:
		GOTO_ERROR_ON((tuple->TupleDataLen != 3) &&
			(tuple->TupleDataLen != 5),
			"bfl tpl size");
		sprom->boardflags_lo = tuple->TupleData[1] |
			((u16)tuple->TupleData[2] << 8);
		break;
	case SSB_PCMCIA_CIS_LEDS:
		GOTO_ERROR_ON(tuple->TupleDataLen != 5,
			"leds tpl size");
		sprom->gpio0 = tuple->TupleData[1];
		sprom->gpio1 = tuple->TupleData[2];
		sprom->gpio2 = tuple->TupleData[3];
		sprom->gpio3 = tuple->TupleData[4];
		break;
	}
	return -ENOSPC; /* continue with next entry */

error:
	pr_err("PCMCIA: Failed to fetch device invariants: %s\n",
	       error_description);
	return -ENODEV;
}