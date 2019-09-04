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
typedef  unsigned char u8 ;
struct pcmidi_sustain {int in_use; unsigned char status; unsigned char note; unsigned char velocity; int /*<<< orphan*/  timer; } ;
struct pcmidi_snd {int midi_channel; int midi_octave; int /*<<< orphan*/  midi_sustain; struct pcmidi_sustain* sustained_notes; scalar_t__ midi_sustain_mode; } ;

/* Variables and functions */
 unsigned char PCMIDI_MIDDLE_C ; 
 unsigned int PCMIDI_SUSTAINED_MAX ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmidi_send_note (struct pcmidi_snd*,unsigned char,unsigned char,unsigned char) ; 

__attribute__((used)) static int pcmidi_handle_report3(struct pcmidi_snd *pm, u8 *data, int size)
{
	struct pcmidi_sustain *pms;
	unsigned i, j;
	unsigned char status, note, velocity;

	unsigned num_notes = (size-1)/2;
	for (j = 0; j < num_notes; j++)	{
		note = data[j*2+1];
		velocity = data[j*2+2];

		if (note < 0x81) { /* note on */
			status = 128 + 16 + pm->midi_channel; /* 1001nnnn */
			note = note - 0x54 + PCMIDI_MIDDLE_C +
				(pm->midi_octave * 12);
			if (0 == velocity)
				velocity = 1; /* force note on */
		} else { /* note off */
			status = 128 + pm->midi_channel; /* 1000nnnn */
			note = note - 0x94 + PCMIDI_MIDDLE_C +
				(pm->midi_octave*12);

			if (pm->midi_sustain_mode) {
				for (i = 0; i < PCMIDI_SUSTAINED_MAX; i++) {
					pms = &pm->sustained_notes[i];
					if (!pms->in_use) {
						pms->status = status;
						pms->note = note;
						pms->velocity = velocity;
						pms->in_use = 1;

						mod_timer(&pms->timer,
							jiffies +
					msecs_to_jiffies(pm->midi_sustain));
						return 1;
					}
				}
			}
		}
		pcmidi_send_note(pm, status, note, velocity);
	}

	return 1;
}