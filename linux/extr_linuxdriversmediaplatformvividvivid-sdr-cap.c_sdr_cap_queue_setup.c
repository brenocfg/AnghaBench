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
struct vb2_queue {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int SDR_CAP_SAMPLES_PER_BUF ; 

__attribute__((used)) static int sdr_cap_queue_setup(struct vb2_queue *vq,
		       unsigned *nbuffers, unsigned *nplanes,
		       unsigned sizes[], struct device *alloc_devs[])
{
	/* 2 = max 16-bit sample returned */
	sizes[0] = SDR_CAP_SAMPLES_PER_BUF * 2;
	*nplanes = 1;
	return 0;
}