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
struct TYPE_2__ {unsigned int first_sendbuf; unsigned int last_sendbuf; } ;
struct qib_pportdata {TYPE_1__ sdma_state; } ;
struct qib_devdata {unsigned int num_pports; struct qib_pportdata* pport; } ;

/* Variables and functions */

__attribute__((used)) static struct qib_pportdata *is_sdma_buf(struct qib_devdata *dd, unsigned i)
{
	struct qib_pportdata *ppd;
	unsigned pidx;

	for (pidx = 0; pidx < dd->num_pports; pidx++) {
		ppd = dd->pport + pidx;
		if (i >= ppd->sdma_state.first_sendbuf &&
		    i < ppd->sdma_state.last_sendbuf)
			return ppd;
	}
	return NULL;
}