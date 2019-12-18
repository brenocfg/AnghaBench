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
struct siw_cq {int dummy; } ;
struct ib_wc {int dummy; } ;
struct ib_cq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  siw_reap_cqe (struct siw_cq*,struct ib_wc*) ; 
 struct siw_cq* to_siw_cq (struct ib_cq*) ; 

int siw_poll_cq(struct ib_cq *base_cq, int num_cqe, struct ib_wc *wc)
{
	struct siw_cq *cq = to_siw_cq(base_cq);
	int i;

	for (i = 0; i < num_cqe; i++) {
		if (!siw_reap_cqe(cq, wc))
			break;
		wc++;
	}
	return i;
}