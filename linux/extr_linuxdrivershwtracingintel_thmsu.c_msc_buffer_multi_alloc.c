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
struct msc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  msc_buffer_multi_free (struct msc*) ; 
 int /*<<< orphan*/  msc_buffer_relink (struct msc*) ; 
 int msc_buffer_win_alloc (struct msc*,unsigned long) ; 

__attribute__((used)) static int msc_buffer_multi_alloc(struct msc *msc, unsigned long *nr_pages,
				  unsigned int nr_wins)
{
	int ret, i;

	for (i = 0; i < nr_wins; i++) {
		ret = msc_buffer_win_alloc(msc, nr_pages[i]);
		if (ret) {
			msc_buffer_multi_free(msc);
			return ret;
		}
	}

	msc_buffer_relink(msc);

	return 0;
}