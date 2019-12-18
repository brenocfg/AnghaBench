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
struct hfc_multi {TYPE_1__* chan; } ;
struct TYPE_2__ {int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  mode_hfcmulti (struct hfc_multi*,int,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void
hfcmulti_pcm(struct hfc_multi *hc, int ch, int slot_tx, int bank_tx,
	     int slot_rx, int bank_rx)
{
	if (slot_tx < 0 || slot_rx < 0 || bank_tx < 0 || bank_rx < 0) {
		/* disable PCM */
		mode_hfcmulti(hc, ch, hc->chan[ch].protocol, -1, 0, -1, 0);
		return;
	}

	/* enable pcm */
	mode_hfcmulti(hc, ch, hc->chan[ch].protocol, slot_tx, bank_tx,
		      slot_rx, bank_rx);
}