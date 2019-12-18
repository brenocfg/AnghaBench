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
struct ppp_file {scalar_t__ kind; scalar_t__ dead; int /*<<< orphan*/  rq; int /*<<< orphan*/  rwait; } ;
struct ppp {scalar_t__ n_channels; int flags; } ;
struct file {struct ppp_file* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;
typedef  int __poll_t ;

/* Variables and functions */
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int EPOLLRDNORM ; 
 int EPOLLWRNORM ; 
 scalar_t__ INTERFACE ; 
 struct ppp* PF_TO_PPP (struct ppp_file*) ; 
 int SC_LOOP_TRAFFIC ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ppp_recv_lock (struct ppp*) ; 
 int /*<<< orphan*/  ppp_recv_unlock (struct ppp*) ; 
 scalar_t__ skb_peek (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __poll_t ppp_poll(struct file *file, poll_table *wait)
{
	struct ppp_file *pf = file->private_data;
	__poll_t mask;

	if (!pf)
		return 0;
	poll_wait(file, &pf->rwait, wait);
	mask = EPOLLOUT | EPOLLWRNORM;
	if (skb_peek(&pf->rq))
		mask |= EPOLLIN | EPOLLRDNORM;
	if (pf->dead)
		mask |= EPOLLHUP;
	else if (pf->kind == INTERFACE) {
		/* see comment in ppp_read */
		struct ppp *ppp = PF_TO_PPP(pf);

		ppp_recv_lock(ppp);
		if (ppp->n_channels == 0 &&
		    (ppp->flags & SC_LOOP_TRAFFIC) == 0)
			mask |= EPOLLIN | EPOLLRDNORM;
		ppp_recv_unlock(ppp);
	}

	return mask;
}