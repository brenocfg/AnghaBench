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
struct snd_cx18_card {int /*<<< orphan*/ * v4l2_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * alsa; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_cx18_card*) ; 
 TYPE_1__* to_cx18 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_cx18_card_free(struct snd_cx18_card *cxsc)
{
	if (cxsc == NULL)
		return;

	if (cxsc->v4l2_dev != NULL)
		to_cx18(cxsc->v4l2_dev)->alsa = NULL;

	/* FIXME - take any other stopping actions needed */

	kfree(cxsc);
}