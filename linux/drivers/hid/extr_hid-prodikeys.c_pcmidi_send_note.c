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
struct pcmidi_snd {int /*<<< orphan*/  rawmidi_in_lock; TYPE_1__* in_substream; int /*<<< orphan*/  in_triggered; } ;
struct TYPE_2__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_rawmidi_receive (TYPE_1__*,unsigned char*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pcmidi_send_note(struct pcmidi_snd *pm,
	unsigned char status, unsigned char note, unsigned char velocity)
{
	unsigned long flags;
	unsigned char buffer[3];

	buffer[0] = status;
	buffer[1] = note;
	buffer[2] = velocity;

	spin_lock_irqsave(&pm->rawmidi_in_lock, flags);

	if (!pm->in_substream)
		goto drop_note;
	if (!test_bit(pm->in_substream->number, &pm->in_triggered))
		goto drop_note;

	snd_rawmidi_receive(pm->in_substream, buffer, 3);

drop_note:
	spin_unlock_irqrestore(&pm->rawmidi_in_lock, flags);

	return;
}