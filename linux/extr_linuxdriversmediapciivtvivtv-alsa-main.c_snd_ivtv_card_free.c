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
struct snd_ivtv_card {int /*<<< orphan*/ * v4l2_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * alsa; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_ivtv_card*) ; 
 TYPE_1__* to_ivtv (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_ivtv_card_free(struct snd_ivtv_card *itvsc)
{
	if (itvsc == NULL)
		return;

	if (itvsc->v4l2_dev != NULL)
		to_ivtv(itvsc->v4l2_dev)->alsa = NULL;

	/* FIXME - take any other stopping actions needed */

	kfree(itvsc);
}