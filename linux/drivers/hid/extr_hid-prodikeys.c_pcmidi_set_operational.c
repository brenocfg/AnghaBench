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
 int pcmidi_get_output_report (struct pcmidi_snd*) ; 
 int /*<<< orphan*/  pcmidi_submit_output_report (struct pcmidi_snd*,int) ; 

__attribute__((used)) static int pcmidi_set_operational(struct pcmidi_snd *pm)
{
	int rc;

	if (pm->ifnum != 1)
		return 0; /* only set up ONCE for interace 1 */

	rc = pcmidi_get_output_report(pm);
	if (rc < 0)
		return rc;
	pcmidi_submit_output_report(pm, 0xc1);
	return 0;
}