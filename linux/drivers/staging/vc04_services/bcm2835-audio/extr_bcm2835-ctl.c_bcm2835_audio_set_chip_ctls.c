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
struct bcm2835_chip {scalar_t__* alsa_stream; } ;

/* Variables and functions */
 int MAX_SUBSTREAMS ; 
 int bcm2835_audio_set_ctls (scalar_t__) ; 

__attribute__((used)) static int bcm2835_audio_set_chip_ctls(struct bcm2835_chip *chip)
{
	int i, err = 0;

	/* change ctls for all substreams */
	for (i = 0; i < MAX_SUBSTREAMS; i++) {
		if (chip->alsa_stream[i]) {
			err = bcm2835_audio_set_ctls(chip->alsa_stream[i]);
			if (err < 0)
				break;
		}
	}
	return err;
}