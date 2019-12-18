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
struct gaudio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR (struct gaudio*,char*) ; 
 int gaudio_open_snd_dev (struct gaudio*) ; 

int gaudio_setup(struct gaudio *card)
{
	int	ret;

	ret = gaudio_open_snd_dev(card);
	if (ret)
		ERROR(card, "we need at least one control device\n");

	return ret;

}