#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_4__ {int a0; int a1; int a2; int a3; } ;
struct ssb_sprom {int boardflags_lo; int revision; int board_rev; int pa0b0; int pa0b1; int pa0b2; int itssi_a; int itssi_bg; int maxpwr_a; int maxpwr_bg; int country_code; int ant_available_a; int ant_available_bg; int gpio0; int gpio1; int gpio2; int gpio3; TYPE_2__ antenna_gain; int /*<<< orphan*/  et1mac; int /*<<< orphan*/  il0mac; scalar_t__ boardflags_hi; } ;
struct ssb_boardinfo {int vendor; } ;
struct ssb_init_invariants {struct ssb_boardinfo boardinfo; struct ssb_sprom sprom; } ;
struct ssb_bus {TYPE_1__* host_sdio; } ;
struct sdio_func_tuple {int code; int* data; int size; struct sdio_func_tuple* next; } ;
struct TYPE_3__ {struct sdio_func_tuple* tuples; } ;

/* Variables and functions */
#define  CISTPL_FUNCE_LAN_NODE_ID 138 
 int ENODEV ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GOTO_ERROR_ON (int,char*) ; 
#define  SSB_SDIO_CIS_ANTENNA 137 
#define  SSB_SDIO_CIS_ANTGAIN 136 
#define  SSB_SDIO_CIS_BFLAGS 135 
#define  SSB_SDIO_CIS_BOARDREV 134 
#define  SSB_SDIO_CIS_CCODE 133 
#define  SSB_SDIO_CIS_ID 132 
#define  SSB_SDIO_CIS_LEDS 131 
#define  SSB_SDIO_CIS_OEMNAME 130 
#define  SSB_SDIO_CIS_PA 129 
#define  SSB_SDIO_CIS_SROMREV 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ssb_sprom*,int,int) ; 
 int /*<<< orphan*/  ssb_sdio_dev (struct ssb_bus*) ; 

int ssb_sdio_get_invariants(struct ssb_bus *bus,
			    struct ssb_init_invariants *iv)
{
	struct ssb_sprom *sprom = &iv->sprom;
	struct ssb_boardinfo *bi = &iv->boardinfo;
	const char *error_description = "none";
	struct sdio_func_tuple *tuple;
	void *mac;

	memset(sprom, 0xFF, sizeof(*sprom));
	sprom->boardflags_lo = 0;
	sprom->boardflags_hi = 0;

	tuple = bus->host_sdio->tuples;
	while (tuple) {
		switch (tuple->code) {
		case 0x22: /* extended function */
			switch (tuple->data[0]) {
			case CISTPL_FUNCE_LAN_NODE_ID:
				GOTO_ERROR_ON((tuple->size != 7) &&
					      (tuple->data[1] != 6),
					      "mac tpl size");
				/* fetch the MAC address. */
				mac = tuple->data + 2;
				memcpy(sprom->il0mac, mac, ETH_ALEN);
				memcpy(sprom->et1mac, mac, ETH_ALEN);
				break;
			default:
				break;
			}
			break;
		case 0x80: /* vendor specific tuple */
			switch (tuple->data[0]) {
			case SSB_SDIO_CIS_SROMREV:
				GOTO_ERROR_ON(tuple->size != 2,
					      "sromrev tpl size");
				sprom->revision = tuple->data[1];
				break;
			case SSB_SDIO_CIS_ID:
				GOTO_ERROR_ON((tuple->size != 5) &&
					      (tuple->size != 7),
					      "id tpl size");
				bi->vendor = tuple->data[1] |
					     (tuple->data[2]<<8);
				break;
			case SSB_SDIO_CIS_BOARDREV:
				GOTO_ERROR_ON(tuple->size != 2,
					      "boardrev tpl size");
				sprom->board_rev = tuple->data[1];
				break;
			case SSB_SDIO_CIS_PA:
				GOTO_ERROR_ON((tuple->size != 9) &&
					      (tuple->size != 10),
					      "pa tpl size");
				sprom->pa0b0 = tuple->data[1] |
					 ((u16)tuple->data[2] << 8);
				sprom->pa0b1 = tuple->data[3] |
					 ((u16)tuple->data[4] << 8);
				sprom->pa0b2 = tuple->data[5] |
					 ((u16)tuple->data[6] << 8);
				sprom->itssi_a = tuple->data[7];
				sprom->itssi_bg = tuple->data[7];
				sprom->maxpwr_a = tuple->data[8];
				sprom->maxpwr_bg = tuple->data[8];
				break;
			case SSB_SDIO_CIS_OEMNAME:
				/* Not present */
				break;
			case SSB_SDIO_CIS_CCODE:
				GOTO_ERROR_ON(tuple->size != 2,
					      "ccode tpl size");
				sprom->country_code = tuple->data[1];
				break;
			case SSB_SDIO_CIS_ANTENNA:
				GOTO_ERROR_ON(tuple->size != 2,
					      "ant tpl size");
				sprom->ant_available_a = tuple->data[1];
				sprom->ant_available_bg = tuple->data[1];
				break;
			case SSB_SDIO_CIS_ANTGAIN:
				GOTO_ERROR_ON(tuple->size != 2,
					      "antg tpl size");
				sprom->antenna_gain.a0 = tuple->data[1];
				sprom->antenna_gain.a1 = tuple->data[1];
				sprom->antenna_gain.a2 = tuple->data[1];
				sprom->antenna_gain.a3 = tuple->data[1];
				break;
			case SSB_SDIO_CIS_BFLAGS:
				GOTO_ERROR_ON((tuple->size != 3) &&
					      (tuple->size != 5),
					      "bfl tpl size");
				sprom->boardflags_lo = tuple->data[1] |
						 ((u16)tuple->data[2] << 8);
				break;
			case SSB_SDIO_CIS_LEDS:
				GOTO_ERROR_ON(tuple->size != 5,
					      "leds tpl size");
				sprom->gpio0 = tuple->data[1];
				sprom->gpio1 = tuple->data[2];
				sprom->gpio2 = tuple->data[3];
				sprom->gpio3 = tuple->data[4];
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
		tuple = tuple->next;
	}

	return 0;
error:
	dev_err(ssb_sdio_dev(bus), "failed to fetch device invariants: %s\n",
		error_description);
	return -ENODEV;
}