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
struct adv7511 {int /*<<< orphan*/ * audio_pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ *) ; 

void adv7511_audio_exit(struct adv7511 *adv7511)
{
	if (adv7511->audio_pdev) {
		platform_device_unregister(adv7511->audio_pdev);
		adv7511->audio_pdev = NULL;
	}
}