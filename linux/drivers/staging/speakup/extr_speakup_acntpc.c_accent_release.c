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
struct TYPE_2__ {scalar_t__ port_tts; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYNTH_IO_EXTENT ; 
 TYPE_1__ speakup_info ; 
 int /*<<< orphan*/  spk_stop_serial_interrupt () ; 
 int /*<<< orphan*/  synth_release_region (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void accent_release(void)
{
	spk_stop_serial_interrupt();
	if (speakup_info.port_tts)
		synth_release_region(speakup_info.port_tts - 1,
				     SYNTH_IO_EXTENT);
	speakup_info.port_tts = 0;
}