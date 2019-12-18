#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int tCCS_min; } ;
struct TYPE_5__ {TYPE_1__ sdr; } ;
struct TYPE_6__ {TYPE_2__ timings; } ;
struct nand_chip {int options; TYPE_3__ data_interface; } ;

/* Variables and functions */
 int NAND_WAIT_TCCS ; 
 scalar_t__ nand_has_setup_data_iface (struct nand_chip*) ; 
 int /*<<< orphan*/  ndelay (int) ; 

__attribute__((used)) static void nand_ccs_delay(struct nand_chip *chip)
{
	/*
	 * The controller already takes care of waiting for tCCS when the RNDIN
	 * or RNDOUT command is sent, return directly.
	 */
	if (!(chip->options & NAND_WAIT_TCCS))
		return;

	/*
	 * Wait tCCS_min if it is correctly defined, otherwise wait 500ns
	 * (which should be safe for all NANDs).
	 */
	if (nand_has_setup_data_iface(chip))
		ndelay(chip->data_interface.timings.sdr.tCCS_min / 1000);
	else
		ndelay(500);
}