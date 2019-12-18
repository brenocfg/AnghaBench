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

/* Variables and functions */
 int /*<<< orphan*/  SYNTH_IO_EXTENT ; 
 int /*<<< orphan*/  spk_stop_serial_interrupt () ; 
 scalar_t__ synth_port ; 
 int /*<<< orphan*/  synth_release_region (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void keynote_release(void)
{
	spk_stop_serial_interrupt();
	if (synth_port)
		synth_release_region(synth_port, SYNTH_IO_EXTENT);
	synth_port = 0;
}