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
struct cx23885_dev {struct cx23885_audio_dev* audio_dev; } ;
struct cx23885_audio_dev {int /*<<< orphan*/  card; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_card_free (int /*<<< orphan*/ ) ; 

void cx23885_audio_unregister(struct cx23885_dev *dev)
{
	struct cx23885_audio_dev *chip = dev->audio_dev;

	snd_card_free(chip->card);
}