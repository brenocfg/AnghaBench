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
struct fst_card_info {scalar_t__ nports; int /*<<< orphan*/  card_no; void* state; } ;

/* Variables and functions */
 scalar_t__ END_SIG ; 
 void* FST_BADVERSION ; 
 void* FST_HALTED ; 
 int FST_RDB (struct fst_card_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ FST_RDL (struct fst_card_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ FST_RDW (struct fst_card_info*,int /*<<< orphan*/ ) ; 
 void* FST_RUNNING ; 
 scalar_t__ SMC_VERSION ; 
 int /*<<< orphan*/  endOfSmcSignature ; 
 int /*<<< orphan*/  numberOfPorts ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  smcVersion ; 
 int /*<<< orphan*/  taskStatus ; 

__attribute__((used)) static void
check_started_ok(struct fst_card_info *card)
{
	int i;

	/* Check structure version and end marker */
	if (FST_RDW(card, smcVersion) != SMC_VERSION) {
		pr_err("Bad shared memory version %d expected %d\n",
		       FST_RDW(card, smcVersion), SMC_VERSION);
		card->state = FST_BADVERSION;
		return;
	}
	if (FST_RDL(card, endOfSmcSignature) != END_SIG) {
		pr_err("Missing shared memory signature\n");
		card->state = FST_BADVERSION;
		return;
	}
	/* Firmware status flag, 0x00 = initialising, 0x01 = OK, 0xFF = fail */
	if ((i = FST_RDB(card, taskStatus)) == 0x01) {
		card->state = FST_RUNNING;
	} else if (i == 0xFF) {
		pr_err("Firmware initialisation failed. Card halted\n");
		card->state = FST_HALTED;
		return;
	} else if (i != 0x00) {
		pr_err("Unknown firmware status 0x%x\n", i);
		card->state = FST_HALTED;
		return;
	}

	/* Finally check the number of ports reported by firmware against the
	 * number we assumed at card detection. Should never happen with
	 * existing firmware etc so we just report it for the moment.
	 */
	if (FST_RDL(card, numberOfPorts) != card->nports) {
		pr_warn("Port count mismatch on card %d.  Firmware thinks %d we say %d\n",
			card->card_no,
			FST_RDL(card, numberOfPorts), card->nports);
	}
}