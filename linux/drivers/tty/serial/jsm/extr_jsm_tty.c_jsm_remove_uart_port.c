#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  line; } ;
struct jsm_channel {TYPE_1__ uart_port; } ;
struct jsm_board {int nasync; int maxports; int /*<<< orphan*/  pci_dev; struct jsm_channel** channels; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  INIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsm_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  jsm_uart_driver ; 
 int /*<<< orphan*/  linemap ; 
 int /*<<< orphan*/  uart_remove_one_port (int /*<<< orphan*/ *,TYPE_1__*) ; 

int jsm_remove_uart_port(struct jsm_board *brd)
{
	int i;
	struct jsm_channel *ch;

	if (!brd)
		return -ENXIO;

	jsm_dbg(INIT, &brd->pci_dev, "start\n");

	/*
	 * Initialize board structure elements.
	 */

	brd->nasync = brd->maxports;

	/* Set up channel variables */
	for (i = 0; i < brd->nasync; i++) {

		if (!brd->channels[i])
			continue;

		ch = brd->channels[i];

		clear_bit(ch->uart_port.line, linemap);
		uart_remove_one_port(&jsm_uart_driver, &brd->channels[i]->uart_port);
	}

	jsm_dbg(INIT, &brd->pci_dev, "finish\n");
	return 0;
}