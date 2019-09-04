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
typedef  int /*<<< orphan*/  u8 ;
struct pcmidi_snd {int dummy; } ;

/* Variables and functions */
 int pcmidi_handle_report1 (struct pcmidi_snd*,int /*<<< orphan*/ *) ; 
 int pcmidi_handle_report3 (struct pcmidi_snd*,int /*<<< orphan*/ *,int) ; 
 int pcmidi_handle_report4 (struct pcmidi_snd*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pcmidi_handle_report(
	struct pcmidi_snd *pm, unsigned report_id, u8 *data, int size)
{
	int ret = 0;

	switch (report_id) {
	case 0x01: /* midi keys (qwerty)*/
		ret = pcmidi_handle_report1(pm, data);
		break;
	case 0x03: /* midi keyboard (musical)*/
		ret = pcmidi_handle_report3(pm, data, size);
		break;
	case 0x04: /* multimedia/midi keys (qwerty)*/
		ret = pcmidi_handle_report4(pm, data);
		break;
	}
	return ret;
}