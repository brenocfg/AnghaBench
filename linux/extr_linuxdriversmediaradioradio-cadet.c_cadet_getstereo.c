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
struct cadet {scalar_t__ io; int /*<<< orphan*/  is_fm_band; } ;

/* Variables and functions */
 int V4L2_TUNER_SUB_MONO ; 
 int V4L2_TUNER_SUB_STEREO ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int,scalar_t__) ; 

__attribute__((used)) static int cadet_getstereo(struct cadet *dev)
{
	int ret = V4L2_TUNER_SUB_MONO;

	if (!dev->is_fm_band)	/* Only FM has stereo capability! */
		return V4L2_TUNER_SUB_MONO;

	outb(7, dev->io);          /* Select tuner control */
	if ((inb(dev->io + 1) & 0x40) == 0)
		ret = V4L2_TUNER_SUB_STEREO;
	return ret;
}