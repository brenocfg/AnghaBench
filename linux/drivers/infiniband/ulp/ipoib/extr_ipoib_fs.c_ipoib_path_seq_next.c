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
struct seq_file {int dummy; } ;
typedef  void ipoib_path_iter ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 scalar_t__ ipoib_path_iter_next (void*) ; 
 int /*<<< orphan*/  kfree (void*) ; 

__attribute__((used)) static void *ipoib_path_seq_next(struct seq_file *file, void *iter_ptr,
				   loff_t *pos)
{
	struct ipoib_path_iter *iter = iter_ptr;

	(*pos)++;

	if (ipoib_path_iter_next(iter)) {
		kfree(iter);
		return NULL;
	}

	return iter;
}