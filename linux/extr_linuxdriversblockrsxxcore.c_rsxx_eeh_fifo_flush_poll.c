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
struct rsxx_cardinfo {scalar_t__ regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_TO_DEV (struct rsxx_cardinfo*) ; 
 scalar_t__ PCI_RECONFIG ; 
 unsigned int RSXX_FLUSH_BUSY ; 
 unsigned int RSXX_FLUSH_TIMEOUT ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 unsigned int ioread32 (scalar_t__) ; 
 int /*<<< orphan*/  ssleep (int) ; 

__attribute__((used)) static int rsxx_eeh_fifo_flush_poll(struct rsxx_cardinfo *card)
{
	unsigned int status;
	int iter = 0;

	/* We need to wait for the hardware to reset */
	while (iter++ < 10) {
		status = ioread32(card->regmap + PCI_RECONFIG);

		if (status & RSXX_FLUSH_BUSY) {
			ssleep(1);
			continue;
		}

		if (status & RSXX_FLUSH_TIMEOUT)
			dev_warn(CARD_TO_DEV(card), "HW: flash controller timeout\n");
		return 0;
	}

	/* Hardware failed resetting itself. */
	return -1;
}