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
struct timer_list {int dummy; } ;
struct pcmidi_sustain {scalar_t__ in_use; int /*<<< orphan*/  velocity; int /*<<< orphan*/  note; int /*<<< orphan*/  status; int /*<<< orphan*/  pm; } ;

/* Variables and functions */
 struct pcmidi_sustain* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcmidi_send_note (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pcmidi_sustain* pms ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void pcmidi_sustained_note_release(struct timer_list *t)
{
	struct pcmidi_sustain *pms = from_timer(pms, t, timer);

	pcmidi_send_note(pms->pm, pms->status, pms->note, pms->velocity);
	pms->in_use = 0;
}