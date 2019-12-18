#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct urb {int status; struct intr_pkt* transfer_buffer; struct uea_softc* context; } ;
struct uea_softc {int /*<<< orphan*/  urb_int; int /*<<< orphan*/  (* dispatch_cmv ) (struct uea_softc*,struct intr_pkt*) ;int /*<<< orphan*/  (* schedule_load_page ) (struct uea_softc*,struct intr_pkt*) ;scalar_t__ booting; } ;
struct intr_pkt {int bType; int /*<<< orphan*/  wInterrupt; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INS_TO_USBDEV (struct uea_softc*) ; 
#define  INT_INCOMINGCMV 129 
#define  INT_LOADSWAPPAGE 128 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct uea_softc*,struct intr_pkt*) ; 
 int /*<<< orphan*/  stub2 (struct uea_softc*,struct intr_pkt*) ; 
 int /*<<< orphan*/  uea_enters (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uea_err (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  usb_submit_urb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void uea_intr(struct urb *urb)
{
	struct uea_softc *sc = urb->context;
	struct intr_pkt *intr = urb->transfer_buffer;
	int status = urb->status;

	uea_enters(INS_TO_USBDEV(sc));

	if (unlikely(status < 0)) {
		uea_err(INS_TO_USBDEV(sc), "uea_intr() failed with %d\n",
		       status);
		return;
	}

	/* device-to-host interrupt */
	if (intr->bType != 0x08 || sc->booting) {
		uea_err(INS_TO_USBDEV(sc), "wrong interrupt\n");
		goto resubmit;
	}

	switch (le16_to_cpu(intr->wInterrupt)) {
	case INT_LOADSWAPPAGE:
		sc->schedule_load_page(sc, intr);
		break;

	case INT_INCOMINGCMV:
		sc->dispatch_cmv(sc, intr);
		break;

	default:
		uea_err(INS_TO_USBDEV(sc), "unknown interrupt %u\n",
		       le16_to_cpu(intr->wInterrupt));
	}

resubmit:
	usb_submit_urb(sc->urb_int, GFP_ATOMIC);
}