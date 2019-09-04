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
struct cx88_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MO_AUD_DMACNTRL ; 
 int cx_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx_write (int /*<<< orphan*/ ,int) ; 

int cx88_stop_audio_dma(struct cx88_core *core)
{
	/* If downstream RISC is enabled, bail out; ALSA is managing DMA */
	if (cx_read(MO_AUD_DMACNTRL) & 0x10)
		return 0;

	/* stop dma */
	cx_write(MO_AUD_DMACNTRL, 0x0000);

	return 0;
}