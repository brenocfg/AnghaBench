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
typedef  scalar_t__ u8 ;
struct pcan_pccard {scalar_t__ ccr; scalar_t__ ioport_addr; } ;

/* Variables and functions */
 int PCC_CCR ; 
 scalar_t__ PCC_COMN_OFF ; 
 int /*<<< orphan*/  iowrite8 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void pcan_write_reg(struct pcan_pccard *card, int port, u8 v)
{
	/* cache ccr value */
	if (port == PCC_CCR) {
		if (card->ccr == v)
			return;
		card->ccr = v;
	}

	iowrite8(v, card->ioport_addr + PCC_COMN_OFF + port);
}