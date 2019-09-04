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
struct pcmidi_sustain {int /*<<< orphan*/  timer; struct pcmidi_snd* pm; scalar_t__ in_use; } ;
struct pcmidi_snd {struct pcmidi_sustain* sustained_notes; } ;

/* Variables and functions */
 unsigned int PCMIDI_SUSTAINED_MAX ; 
 int /*<<< orphan*/  pcmidi_sustained_note_release ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_sustain_timers(struct pcmidi_snd *pm)
{
	struct pcmidi_sustain *pms;
	unsigned i;

	for (i = 0; i < PCMIDI_SUSTAINED_MAX; i++) {
		pms = &pm->sustained_notes[i];
		pms->in_use = 0;
		pms->pm = pm;
		timer_setup(&pms->timer, pcmidi_sustained_note_release, 0);
	}
}