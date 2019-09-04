#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pcmidi_snd {scalar_t__ card; TYPE_2__* pk; } ;
struct TYPE_4__ {TYPE_1__* hdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_card_disconnect (scalar_t__) ; 
 int /*<<< orphan*/  snd_card_free_when_closed (scalar_t__) ; 
 int /*<<< orphan*/  stop_sustain_timers (struct pcmidi_snd*) ; 
 int /*<<< orphan*/  sysfs_device_attr_channel ; 
 int /*<<< orphan*/  sysfs_device_attr_octave ; 
 int /*<<< orphan*/  sysfs_device_attr_sustain ; 

__attribute__((used)) static int pcmidi_snd_terminate(struct pcmidi_snd *pm)
{
	if (pm->card) {
		stop_sustain_timers(pm);

		device_remove_file(&pm->pk->hdev->dev,
			sysfs_device_attr_channel);
		device_remove_file(&pm->pk->hdev->dev,
			sysfs_device_attr_sustain);
		device_remove_file(&pm->pk->hdev->dev,
			sysfs_device_attr_octave);

		snd_card_disconnect(pm->card);
		snd_card_free_when_closed(pm->card);
	}

	return 0;
}