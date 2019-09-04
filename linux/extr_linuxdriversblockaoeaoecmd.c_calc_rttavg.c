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
struct aoetgt {scalar_t__ maxout; scalar_t__ nframes; scalar_t__ ssthresh; scalar_t__ nout; scalar_t__ next_cwnd; } ;
struct aoedev {long rttavg; long rttdev; } ;

/* Variables and functions */
 long RTTDSCALE ; 
 long RTTSCALE ; 

__attribute__((used)) static void
calc_rttavg(struct aoedev *d, struct aoetgt *t, int rtt)
{
	register long n;

	n = rtt;

	/* cf. Congestion Avoidance and Control, Jacobson & Karels, 1988 */
	n -= d->rttavg >> RTTSCALE;
	d->rttavg += n;
	if (n < 0)
		n = -n;
	n -= d->rttdev >> RTTDSCALE;
	d->rttdev += n;

	if (!t || t->maxout >= t->nframes)
		return;
	if (t->maxout < t->ssthresh)
		t->maxout += 1;
	else if (t->nout == t->maxout && t->next_cwnd-- == 0) {
		t->maxout += 1;
		t->next_cwnd = t->maxout;
	}
}