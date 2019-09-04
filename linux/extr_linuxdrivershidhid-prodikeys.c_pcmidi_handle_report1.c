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
typedef  int u8 ;
typedef  int u32 ;
struct pcmidi_snd {int midi_octave; int midi_sustain_mode; scalar_t__ midi_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_hid (char*,scalar_t__,...) ; 

__attribute__((used)) static int pcmidi_handle_report1(struct pcmidi_snd *pm, u8 *data)
{
	u32 bit_mask;

	bit_mask = data[1];
	bit_mask = (bit_mask << 8) | data[2];
	bit_mask = (bit_mask << 8) | data[3];

	dbg_hid("pcmidi mode: %d\n", pm->midi_mode);

	/*KEY_MAIL or octave down*/
	if (pm->midi_mode && bit_mask == 0x004000) {
		/* octave down */
		pm->midi_octave--;
		if (pm->midi_octave < -2)
			pm->midi_octave = -2;
		dbg_hid("pcmidi mode: %d octave: %d\n",
			pm->midi_mode, pm->midi_octave);
		return 1;
	}
	/*KEY_WWW or sustain*/
	else if (pm->midi_mode && bit_mask == 0x000004) {
		/* sustain on/off*/
		pm->midi_sustain_mode ^= 0x1;
		return 1;
	}

	return 0; /* continue key processing */
}