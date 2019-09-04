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
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  (* dr_release_t ) (struct device*,void*) ;
typedef  int /*<<< orphan*/  dr_match_t ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  devres_free (void*) ; 
 void* devres_remove (struct device*,int /*<<< orphan*/  (*) (struct device*,void*),int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub1 (struct device*,void*) ; 
 scalar_t__ unlikely (int) ; 

int devres_release(struct device *dev, dr_release_t release,
		   dr_match_t match, void *match_data)
{
	void *res;

	res = devres_remove(dev, release, match, match_data);
	if (unlikely(!res))
		return -ENOENT;

	(*release)(dev, res);
	devres_free(res);
	return 0;
}