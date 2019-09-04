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
struct pcmidi_snd {int ifnum; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcmidi_get_output_report (struct pcmidi_snd*) ; 
 int /*<<< orphan*/  pcmidi_submit_output_report (struct pcmidi_snd*,int) ; 

__attribute__((used)) static int pcmidi_set_operational(struct pcmidi_snd *pm)
{
	if (pm->ifnum != 1)
		return 0; /* only set up ONCE for interace 1 */

	pcmidi_get_output_report(pm);
	pcmidi_submit_output_report(pm, 0xc1);
	return 0;
}