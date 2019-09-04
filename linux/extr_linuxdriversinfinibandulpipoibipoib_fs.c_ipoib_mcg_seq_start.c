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
struct seq_file {int /*<<< orphan*/  private; } ;
typedef  void ipoib_mcast_iter ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 void* ipoib_mcast_iter_init (int /*<<< orphan*/ ) ; 
 scalar_t__ ipoib_mcast_iter_next (void*) ; 
 int /*<<< orphan*/  kfree (void*) ; 

__attribute__((used)) static void *ipoib_mcg_seq_start(struct seq_file *file, loff_t *pos)
{
	struct ipoib_mcast_iter *iter;
	loff_t n = *pos;

	iter = ipoib_mcast_iter_init(file->private);
	if (!iter)
		return NULL;

	while (n--) {
		if (ipoib_mcast_iter_next(iter)) {
			kfree(iter);
			return NULL;
		}
	}

	return iter;
}