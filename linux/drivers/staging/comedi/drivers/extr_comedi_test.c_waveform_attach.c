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
struct comedi_device {int dummy; } ;
struct comedi_devconfig {int* options; } ;

/* Variables and functions */
 int waveform_common_attach (struct comedi_device*,int,int) ; 

__attribute__((used)) static int waveform_attach(struct comedi_device *dev,
			   struct comedi_devconfig *it)
{
	int amplitude = it->options[0];
	int period = it->options[1];

	/* set default amplitude and period */
	if (amplitude <= 0)
		amplitude = 1000000;	/* 1 volt */
	if (period <= 0)
		period = 100000;	/* 0.1 sec */

	return waveform_common_attach(dev, amplitude, period);
}