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
struct snd_cobalt_card {int dummy; } ;
struct snd_card {int dummy; } ;
struct cobalt_stream {struct snd_cobalt_card* alsa; struct cobalt* cobalt; } ;
struct cobalt {TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_DEFAULT_IDX1 ; 
 int /*<<< orphan*/  SNDRV_DEFAULT_STR1 ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  cobalt_err (char*,int) ; 
 int /*<<< orphan*/  kfree (struct snd_cobalt_card*) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 
 int snd_card_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_card**) ; 
 int snd_card_register (struct snd_card*) ; 
 int snd_cobalt_card_create (struct cobalt_stream*,struct snd_card*,struct snd_cobalt_card**) ; 
 int /*<<< orphan*/  snd_cobalt_card_set_names (struct snd_cobalt_card*) ; 
 int snd_cobalt_pcm_create (struct snd_cobalt_card*) ; 

int cobalt_alsa_init(struct cobalt_stream *s)
{
	struct cobalt *cobalt = s->cobalt;
	struct snd_card *sc = NULL;
	struct snd_cobalt_card *cobsc;
	int ret;

	/* Numbrs steps from "Writing an ALSA Driver" by Takashi Iwai */

	/* (1) Check and increment the device index */
	/* This is a no-op for us.  We'll use the cobalt->instance */

	/* (2) Create a card instance */
	ret = snd_card_new(&cobalt->pci_dev->dev, SNDRV_DEFAULT_IDX1,
			   SNDRV_DEFAULT_STR1, THIS_MODULE, 0, &sc);
	if (ret) {
		cobalt_err("snd_card_new() failed with err %d\n", ret);
		goto err_exit;
	}

	/* (3) Create a main component */
	ret = snd_cobalt_card_create(s, sc, &cobsc);
	if (ret) {
		cobalt_err("snd_cobalt_card_create() failed with err %d\n",
			   ret);
		goto err_exit_free;
	}

	/* (4) Set the driver ID and name strings */
	snd_cobalt_card_set_names(cobsc);

	ret = snd_cobalt_pcm_create(cobsc);
	if (ret) {
		cobalt_err("snd_cobalt_pcm_create() failed with err %d\n",
			   ret);
		goto err_exit_free;
	}
	/* FIXME - proc files */

	/* (7) Set the driver data and return 0 */
	/* We do this out of normal order for PCI drivers to avoid races */
	s->alsa = cobsc;

	/* (6) Register the card instance */
	ret = snd_card_register(sc);
	if (ret) {
		s->alsa = NULL;
		cobalt_err("snd_card_register() failed with err %d\n", ret);
		goto err_exit_free;
	}

	return 0;

err_exit_free:
	if (sc != NULL)
		snd_card_free(sc);
	kfree(cobsc);
err_exit:
	return ret;
}