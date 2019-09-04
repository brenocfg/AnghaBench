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
struct pcmidi_snd {unsigned int* last_key; int fn_state; int midi_mode; int midi_octave; int /*<<< orphan*/  input_ep82; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_KEY ; 
 unsigned int KEY_ADDRESSBOOK ; 
 unsigned int KEY_CALENDAR ; 
 unsigned int KEY_CLOSE ; 
 unsigned int KEY_COFFEE ; 
 unsigned int KEY_DOCUMENTS ; 
 unsigned int KEY_FORWARDMAIL ; 
 unsigned int KEY_HELP ; 
 unsigned int KEY_MESSENGER ; 
 unsigned int KEY_NEW ; 
 unsigned int KEY_OPEN ; 
 unsigned int KEY_PRINT ; 
 unsigned int KEY_REDO ; 
 unsigned int KEY_REPLY ; 
 unsigned int KEY_SAVE ; 
 unsigned int KEY_SEND ; 
 unsigned int KEY_SPELLCHECK ; 
 unsigned int KEY_SPREADSHEET ; 
 unsigned int KEY_UNDO ; 
 unsigned int KEY_WORDPROCESSOR ; 
 int /*<<< orphan*/  dbg_hid (char*,int,...) ; 
 int /*<<< orphan*/  input_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  pcmidi_submit_output_report (struct pcmidi_snd*,int) ; 

__attribute__((used)) static int pcmidi_handle_report4(struct pcmidi_snd *pm, u8 *data)
{
	unsigned	key;
	u32		bit_mask;
	u32		bit_index;

	bit_mask = data[1];
	bit_mask = (bit_mask << 8) | data[2];
	bit_mask = (bit_mask << 8) | data[3];

	/* break keys */
	for (bit_index = 0; bit_index < 24; bit_index++) {
		if (!((0x01 << bit_index) & bit_mask)) {
			input_event(pm->input_ep82, EV_KEY,
				pm->last_key[bit_index], 0);
			pm->last_key[bit_index] = 0;
		}
	}

	/* make keys */
	for (bit_index = 0; bit_index < 24; bit_index++) {
		key = 0;
		switch ((0x01 << bit_index) & bit_mask) {
		case 0x000010: /* Fn lock*/
			pm->fn_state ^= 0x000010;
			if (pm->fn_state)
				pcmidi_submit_output_report(pm, 0xc5);
			else
				pcmidi_submit_output_report(pm, 0xc6);
			continue;
		case 0x020000: /* midi launcher..send a key (qwerty) or not? */
			pcmidi_submit_output_report(pm, 0xc1);
			pm->midi_mode ^= 0x01;

			dbg_hid("pcmidi mode: %d\n", pm->midi_mode);
			continue;
		case 0x100000: /* KEY_MESSENGER or octave up */
			dbg_hid("pcmidi mode: %d\n", pm->midi_mode);
			if (pm->midi_mode) {
				pm->midi_octave++;
				if (pm->midi_octave > 2)
					pm->midi_octave = 2;
				dbg_hid("pcmidi mode: %d octave: %d\n",
					pm->midi_mode, pm->midi_octave);
				continue;
			} else
				key = KEY_MESSENGER;
			break;
		case 0x400000:
			key = KEY_CALENDAR;
			break;
		case 0x080000:
			key = KEY_ADDRESSBOOK;
			break;
		case 0x040000:
			key = KEY_DOCUMENTS;
			break;
		case 0x800000:
			key = KEY_WORDPROCESSOR;
			break;
		case 0x200000:
			key = KEY_SPREADSHEET;
			break;
		case 0x010000:
			key = KEY_COFFEE;
			break;
		case 0x000100:
			key = KEY_HELP;
			break;
		case 0x000200:
			key = KEY_SEND;
			break;
		case 0x000400:
			key = KEY_REPLY;
			break;
		case 0x000800:
			key = KEY_FORWARDMAIL;
			break;
		case 0x001000:
			key = KEY_NEW;
			break;
		case 0x002000:
			key = KEY_OPEN;
			break;
		case 0x004000:
			key = KEY_CLOSE;
			break;
		case 0x008000:
			key = KEY_SAVE;
			break;
		case 0x000001:
			key = KEY_UNDO;
			break;
		case 0x000002:
			key = KEY_REDO;
			break;
		case 0x000004:
			key = KEY_SPELLCHECK;
			break;
		case 0x000008:
			key = KEY_PRINT;
			break;
		}
		if (key) {
			input_event(pm->input_ep82, EV_KEY, key, 1);
			pm->last_key[bit_index] = key;
		}
	}

	return 1;
}