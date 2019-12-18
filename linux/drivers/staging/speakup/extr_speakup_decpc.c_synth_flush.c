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
struct spk_synth {int dummy; } ;
struct TYPE_2__ {scalar_t__ port_tts; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL_flush ; 
 int /*<<< orphan*/  DMA_sync ; 
 int /*<<< orphan*/  STAT_dma_ready ; 
 int STAT_dma_state ; 
 int STAT_flushing ; 
 int dma_state ; 
 scalar_t__ dt_ctrl (int /*<<< orphan*/ ) ; 
 int dt_getstatus () ; 
 scalar_t__ dt_waitbit (int /*<<< orphan*/ ) ; 
 scalar_t__ in_escape ; 
 int is_flushing ; 
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__ speakup_info ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void synth_flush(struct spk_synth *synth)
{
	int timeout = 10;

	if (is_flushing)
		return;
	is_flushing = 4;
	in_escape = 0;
	while (dt_ctrl(CTRL_flush)) {
		if (--timeout == 0)
			break;
		udelay(50);
	}
	for (timeout = 0; timeout < 10; timeout++) {
		if (dt_waitbit(STAT_dma_ready))
			break;
		udelay(50);
	}
	outb_p(DMA_sync, speakup_info.port_tts + 4);
	outb_p(0, speakup_info.port_tts + 4);
	udelay(100);
	for (timeout = 0; timeout < 10; timeout++) {
		if (!(dt_getstatus() & STAT_flushing))
			break;
		udelay(50);
	}
	dma_state = dt_getstatus() & STAT_dma_state;
	dma_state ^= STAT_dma_state;
	is_flushing = 0;
}