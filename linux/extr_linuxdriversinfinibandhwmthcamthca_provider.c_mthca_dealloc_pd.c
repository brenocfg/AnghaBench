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
struct ib_pd {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ib_pd*) ; 
 int /*<<< orphan*/  mthca_pd_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mpd (struct ib_pd*) ; 

__attribute__((used)) static int mthca_dealloc_pd(struct ib_pd *pd)
{
	mthca_pd_free(to_mdev(pd->device), to_mpd(pd));
	kfree(pd);

	return 0;
}