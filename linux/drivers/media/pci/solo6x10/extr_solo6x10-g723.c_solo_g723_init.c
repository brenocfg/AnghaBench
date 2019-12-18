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
struct solo_dev {TYPE_2__* pdev; int /*<<< orphan*/  nr_chans; struct snd_card* snd_card; TYPE_1__* vfd; int /*<<< orphan*/  snd_users; } ;
struct snd_kcontrol_new {int /*<<< orphan*/  count; } ;
struct snd_device_ops {int dummy; } ;
struct snd_card {char* driver; char* shortname; char* mixername; int /*<<< orphan*/  longname; } ;
struct TYPE_4__ {int irq; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int num; } ;

/* Variables and functions */
 int /*<<< orphan*/  SNDRV_DEFAULT_IDX1 ; 
 int /*<<< orphan*/  SNDRV_DEV_LOWLEVEL ; 
 char* SOLO6X10_NAME ; 
 int /*<<< orphan*/  THIS_MODULE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,char*) ; 
 char* pci_name (TYPE_2__*) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 
 int snd_card_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snd_card**) ; 
 int snd_card_register (struct snd_card*) ; 
 int snd_ctl_add (struct snd_card*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_ctl_new1 (struct snd_kcontrol_new*,struct solo_dev*) ; 
 int snd_device_new (struct snd_card*,int /*<<< orphan*/ ,struct solo_dev*,struct snd_device_ops*) ; 
 struct snd_kcontrol_new snd_solo_capture_volume ; 
 int /*<<< orphan*/  solo_g723_config (struct solo_dev*) ; 
 int solo_snd_pcm_init (struct solo_dev*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 
 int /*<<< orphan*/  strscpy (char*,char*,int) ; 

int solo_g723_init(struct solo_dev *solo_dev)
{
	static struct snd_device_ops ops = { };
	struct snd_card *card;
	struct snd_kcontrol_new kctl;
	char name[32];
	int ret;

	atomic_set(&solo_dev->snd_users, 0);

	/* Allows for easier mapping between video and audio */
	sprintf(name, "Softlogic%d", solo_dev->vfd->num);

	ret = snd_card_new(&solo_dev->pdev->dev,
			   SNDRV_DEFAULT_IDX1, name, THIS_MODULE, 0,
			   &solo_dev->snd_card);
	if (ret < 0)
		return ret;

	card = solo_dev->snd_card;

	strscpy(card->driver, SOLO6X10_NAME, sizeof(card->driver));
	strscpy(card->shortname, "SOLO-6x10 Audio", sizeof(card->shortname));
	sprintf(card->longname, "%s on %s IRQ %d", card->shortname,
		pci_name(solo_dev->pdev), solo_dev->pdev->irq);

	ret = snd_device_new(card, SNDRV_DEV_LOWLEVEL, solo_dev, &ops);
	if (ret < 0)
		goto snd_error;

	/* Mixer controls */
	strscpy(card->mixername, "SOLO-6x10", sizeof(card->mixername));
	kctl = snd_solo_capture_volume;
	kctl.count = solo_dev->nr_chans;

	ret = snd_ctl_add(card, snd_ctl_new1(&kctl, solo_dev));
	if (ret < 0)
		return ret;

	ret = solo_snd_pcm_init(solo_dev);
	if (ret < 0)
		goto snd_error;

	ret = snd_card_register(card);
	if (ret < 0)
		goto snd_error;

	solo_g723_config(solo_dev);

	dev_info(&solo_dev->pdev->dev, "Alsa sound card as %s\n", name);

	return 0;

snd_error:
	snd_card_free(card);
	return ret;
}