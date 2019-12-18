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
struct snd_rawmidi_substream {TYPE_1__* rmidi; } ;
struct pcmidi_snd {int in_triggered; } ;
struct TYPE_2__ {struct pcmidi_snd* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_hid (char*,int) ; 

__attribute__((used)) static void pcmidi_in_trigger(struct snd_rawmidi_substream *substream, int up)
{
	struct pcmidi_snd *pm = substream->rmidi->private_data;

	dbg_hid("pcmidi in trigger %d\n", up);

	pm->in_triggered = up;
}