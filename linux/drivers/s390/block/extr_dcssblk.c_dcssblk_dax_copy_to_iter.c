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
struct iov_iter {int dummy; } ;
struct dax_device {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 size_t copy_to_iter (void*,size_t,struct iov_iter*) ; 

__attribute__((used)) static size_t dcssblk_dax_copy_to_iter(struct dax_device *dax_dev,
		pgoff_t pgoff, void *addr, size_t bytes, struct iov_iter *i)
{
	return copy_to_iter(addr, bytes, i);
}