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
struct snd_card {int dummy; } ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devno ; 
 struct snd_card* pci_get_drvdata (struct pci_dev*) ; 
 int /*<<< orphan*/  snd_card_free (struct snd_card*) ; 

__attribute__((used)) static void cx88_audio_finidev(struct pci_dev *pci)
{
	struct snd_card *card = pci_get_drvdata(pci);

	snd_card_free(card);

	devno--;
}