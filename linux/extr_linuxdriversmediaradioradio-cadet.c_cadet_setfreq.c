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
struct cadet {size_t is_fm_band; unsigned int curfreq; int tunestat; scalar_t__ io; scalar_t__ sigstrength; } ;
struct TYPE_2__ {int /*<<< orphan*/  rangehigh; int /*<<< orphan*/  rangelow; } ;

/* Variables and functions */
 TYPE_1__* bands ; 
 int /*<<< orphan*/  cadet_gettune (struct cadet*) ; 
 int /*<<< orphan*/  cadet_settune (struct cadet*,unsigned int) ; 
 unsigned int clamp (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 scalar_t__** sigtable ; 

__attribute__((used)) static void cadet_setfreq(struct cadet *dev, unsigned freq)
{
	unsigned fifo;
	int i, j, test;
	int curvol;

	freq = clamp(freq, bands[dev->is_fm_band].rangelow,
			   bands[dev->is_fm_band].rangehigh);
	dev->curfreq = freq;
	/*
	 * Formulate a fifo command
	 */
	fifo = 0;
	if (dev->is_fm_band) {    /* FM */
		test = 102400;
		freq = freq / 16;       /* Make it kHz */
		freq += 10700;               /* IF is 10700 kHz */
		for (i = 0; i < 14; i++) {
			fifo = fifo << 1;
			if (freq >= test) {
				fifo |= 0x01;
				freq -= test;
			}
			test = test >> 1;
		}
	} else {	/* AM */
		fifo = (freq / 16) + 450;	/* Make it kHz */
		fifo |= 0x100000;		/* Select AM Band */
	}

	/*
	 * Save current volume/mute setting
	 */

	outb(7, dev->io);                /* Select tuner control */
	curvol = inb(dev->io + 1);

	/*
	 * Tune the card
	 */
	for (j = 3; j > -1; j--) {
		cadet_settune(dev, fifo | (j << 16));

		outb(7, dev->io);         /* Select tuner control */
		outb(curvol, dev->io + 1);

		msleep(100);

		cadet_gettune(dev);
		if ((dev->tunestat & 0x40) == 0) {   /* Tuned */
			dev->sigstrength = sigtable[dev->is_fm_band][j];
			goto reset_rds;
		}
	}
	dev->sigstrength = 0;
reset_rds:
	outb(3, dev->io);
	outb(inb(dev->io + 1) & 0x7f, dev->io + 1);
}