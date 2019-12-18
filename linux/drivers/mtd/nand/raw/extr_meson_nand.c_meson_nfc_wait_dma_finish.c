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
 int /*<<< orphan*/  DMA_BUSY_TIMEOUT ; 
 int /*<<< orphan*/  meson_nfc_drain_cmd (struct meson_nfc*) ; 
 int meson_nfc_wait_cmd_finish (struct meson_nfc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int meson_nfc_wait_dma_finish(struct meson_nfc *nfc)
{
	meson_nfc_drain_cmd(nfc);

	return meson_nfc_wait_cmd_finish(nfc, DMA_BUSY_TIMEOUT);
}