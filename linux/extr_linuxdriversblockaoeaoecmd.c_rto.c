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
struct aoedev {int rttavg; int rttdev; } ;

/* Variables and functions */
 int RTTDSCALE ; 
 int RTTSCALE ; 

__attribute__((used)) static long
rto(struct aoedev *d)
{
	long t;

	t = 2 * d->rttavg >> RTTSCALE;
	t += 8 * d->rttdev >> RTTDSCALE;
	if (t == 0)
		t = 1;

	return t;
}