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
struct nfp_cpp_area {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int __nfp_cpp_area_acquire (struct nfp_cpp_area*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int nfp_cpp_area_acquire(struct nfp_cpp_area *area)
{
	int ret;

	mutex_lock(&area->mutex);
	ret = __nfp_cpp_area_acquire(area);
	mutex_unlock(&area->mutex);

	return ret;
}