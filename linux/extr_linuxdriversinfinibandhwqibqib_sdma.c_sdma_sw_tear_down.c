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
struct qib_sdma_state {int dummy; } ;
struct qib_pportdata {struct qib_sdma_state sdma_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdma_put (struct qib_sdma_state*) ; 

__attribute__((used)) static void sdma_sw_tear_down(struct qib_pportdata *ppd)
{
	struct qib_sdma_state *ss = &ppd->sdma_state;

	/* Releasing this reference means the state machine has stopped. */
	sdma_put(ss);
}