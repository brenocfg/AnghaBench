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
struct meson_nfc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  meson_nfc_cmd_idle (struct meson_nfc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void meson_nfc_drain_cmd(struct meson_nfc *nfc)
{
	/*
	 * Insert two commands to make sure all valid commands are finished.
	 *
	 * The Nand flash controller is designed as two stages pipleline -
	 *  a) fetch and b) excute.
	 * There might be cases when the driver see command queue is empty,
	 * but the Nand flash controller still has two commands buffered,
	 * one is fetched into NFC request queue (ready to run), and another
	 * is actively executing. So pushing 2 "IDLE" commands guarantees that
	 * the pipeline is emptied.
	 */
	meson_nfc_cmd_idle(nfc, 0);
	meson_nfc_cmd_idle(nfc, 0);
}