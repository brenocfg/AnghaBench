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
struct iov_iter {int dummy; } ;
struct dax_device {TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  pgoff_t ;
struct TYPE_2__ {size_t (* copy_from_iter ) (struct dax_device*,int /*<<< orphan*/ ,void*,size_t,struct iov_iter*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dax_alive (struct dax_device*) ; 
 size_t stub1 (struct dax_device*,int /*<<< orphan*/ ,void*,size_t,struct iov_iter*) ; 

size_t dax_copy_from_iter(struct dax_device *dax_dev, pgoff_t pgoff, void *addr,
		size_t bytes, struct iov_iter *i)
{
	if (!dax_alive(dax_dev))
		return 0;

	return dax_dev->ops->copy_from_iter(dax_dev, pgoff, addr, bytes, i);
}