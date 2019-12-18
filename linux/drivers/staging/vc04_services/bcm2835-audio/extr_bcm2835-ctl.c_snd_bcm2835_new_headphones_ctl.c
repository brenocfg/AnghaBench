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
struct bcm2835_chip {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  mixername; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int create_ctls (struct bcm2835_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_bcm2835_headphones_ctl ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 

int snd_bcm2835_new_headphones_ctl(struct bcm2835_chip *chip)
{
	strcpy(chip->card->mixername, "Broadcom Mixer");
	return create_ctls(chip, ARRAY_SIZE(snd_bcm2835_headphones_ctl),
			   snd_bcm2835_headphones_ctl);
}