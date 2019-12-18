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
struct msc {scalar_t__ mode; int /*<<< orphan*/  user_count; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int ENOTSUPP ; 
 scalar_t__ MSC_MODE_MULTI ; 
 scalar_t__ MSC_MODE_SINGLE ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int atomic_cmpxchg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int msc_buffer_contig_alloc (struct msc*,unsigned long) ; 
 int msc_buffer_multi_alloc (struct msc*,unsigned long*,unsigned int) ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

__attribute__((used)) static int msc_buffer_alloc(struct msc *msc, unsigned long *nr_pages,
			    unsigned int nr_wins)
{
	int ret;

	/* -1: buffer not allocated */
	if (atomic_read(&msc->user_count) != -1)
		return -EBUSY;

	if (msc->mode == MSC_MODE_SINGLE) {
		if (nr_wins != 1)
			return -EINVAL;

		ret = msc_buffer_contig_alloc(msc, nr_pages[0] << PAGE_SHIFT);
	} else if (msc->mode == MSC_MODE_MULTI) {
		ret = msc_buffer_multi_alloc(msc, nr_pages, nr_wins);
	} else {
		ret = -ENOTSUPP;
	}

	if (!ret) {
		/* allocation should be visible before the counter goes to 0 */
		smp_mb__before_atomic();

		if (WARN_ON_ONCE(atomic_cmpxchg(&msc->user_count, -1, 0) != -1))
			return -EINVAL;
	}

	return ret;
}