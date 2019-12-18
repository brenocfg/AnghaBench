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
struct usbtv {int /*<<< orphan*/ * snd; scalar_t__ udev; int /*<<< orphan*/  snd_trigger; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_card_free (int /*<<< orphan*/ *) ; 

void usbtv_audio_free(struct usbtv *usbtv)
{
	cancel_work_sync(&usbtv->snd_trigger);

	if (usbtv->snd && usbtv->udev) {
		snd_card_free(usbtv->snd);
		usbtv->snd = NULL;
	}
}