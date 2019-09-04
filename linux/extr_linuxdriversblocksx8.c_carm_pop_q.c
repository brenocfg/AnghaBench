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
struct request_queue {int dummy; } ;
struct carm_host {unsigned int wait_q_prod; unsigned int wait_q_cons; struct request_queue** wait_q; } ;

/* Variables and functions */
 unsigned int CARM_MAX_WAIT_Q ; 

__attribute__((used)) static inline struct request_queue *carm_pop_q(struct carm_host *host)
{
	unsigned int idx;

	if (host->wait_q_prod == host->wait_q_cons)
		return NULL;

	idx = host->wait_q_cons % CARM_MAX_WAIT_Q;
	host->wait_q_cons++;

	return host->wait_q[idx];
}