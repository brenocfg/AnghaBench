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
struct snd_card {int /*<<< orphan*/ * private_free; int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_cobalt_card_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void snd_cobalt_card_private_free(struct snd_card *sc)
{
	if (sc == NULL)
		return;
	snd_cobalt_card_free(sc->private_data);
	sc->private_data = NULL;
	sc->private_free = NULL;
}