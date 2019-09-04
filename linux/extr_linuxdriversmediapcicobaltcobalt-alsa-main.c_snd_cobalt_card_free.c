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
struct snd_cobalt_card {TYPE_1__* s; } ;
struct TYPE_2__ {int /*<<< orphan*/ * alsa; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct snd_cobalt_card*) ; 

__attribute__((used)) static void snd_cobalt_card_free(struct snd_cobalt_card *cobsc)
{
	if (cobsc == NULL)
		return;

	cobsc->s->alsa = NULL;

	kfree(cobsc);
}