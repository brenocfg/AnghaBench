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
struct si470x_device {int (* get_register ) (struct si470x_device*,size_t) ;int* registers; size_t band; } ;
struct TYPE_2__ {int rangelow; } ;

/* Variables and functions */
 size_t READCHAN ; 
 int READCHAN_READCHAN ; 
 TYPE_1__* bands ; 
 int si470x_get_step (struct si470x_device*) ; 
 int stub1 (struct si470x_device*,size_t) ; 

__attribute__((used)) static int si470x_get_freq(struct si470x_device *radio, unsigned int *freq)
{
	int chan, retval;

	/* read channel */
	retval = radio->get_register(radio, READCHAN);
	chan = radio->registers[READCHAN] & READCHAN_READCHAN;

	/* Frequency (MHz) = Spacing (kHz) x Channel + Bottom of Band (MHz) */
	*freq = chan * si470x_get_step(radio) + bands[radio->band].rangelow;

	return retval;
}