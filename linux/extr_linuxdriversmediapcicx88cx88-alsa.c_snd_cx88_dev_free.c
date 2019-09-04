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
struct snd_card {struct cx88_audio_dev* private_data; } ;
struct cx88_audio_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_cx88_free (struct cx88_audio_dev*) ; 

__attribute__((used)) static void snd_cx88_dev_free(struct snd_card *card)
{
	struct cx88_audio_dev *chip = card->private_data;

	snd_cx88_free(chip);
}