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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_4__ {int class; scalar_t__ p2; scalar_t__ p1; scalar_t__ ins; } ;
struct TYPE_3__ {int datalen; scalar_t__* params; scalar_t__ seq; scalar_t__ slot; int /*<<< orphan*/  type; } ;
struct pn533_acr122_tx_frame {int datalen; TYPE_2__ apdu; int /*<<< orphan*/ * data; TYPE_1__ ccid; } ;

/* Variables and functions */
 int /*<<< orphan*/  PN533_ACR122_PC_TO_RDR_ESCAPE ; 
 int /*<<< orphan*/  PN533_STD_FRAME_DIR_OUT ; 

__attribute__((used)) static void pn533_acr122_tx_frame_init(void *_frame, u8 cmd_code)
{
	struct pn533_acr122_tx_frame *frame = _frame;

	frame->ccid.type = PN533_ACR122_PC_TO_RDR_ESCAPE;
	/* sizeof(apdu_hdr) + sizeof(datalen) */
	frame->ccid.datalen = sizeof(frame->apdu) + 1;
	frame->ccid.slot = 0;
	frame->ccid.seq = 0;
	frame->ccid.params[0] = 0;
	frame->ccid.params[1] = 0;
	frame->ccid.params[2] = 0;

	frame->data[0] = PN533_STD_FRAME_DIR_OUT;
	frame->data[1] = cmd_code;
	frame->datalen = 2;  /* data[0] + data[1] */

	frame->apdu.class = 0xFF;
	frame->apdu.ins = 0;
	frame->apdu.p1 = 0;
	frame->apdu.p2 = 0;
}