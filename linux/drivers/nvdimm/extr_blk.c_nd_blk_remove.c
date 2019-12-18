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

/* Variables and functions */
 scalar_t__ is_nd_btt (struct device*) ; 
 int /*<<< orphan*/  nvdimm_namespace_detach_btt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_nd_btt (struct device*) ; 

__attribute__((used)) static int nd_blk_remove(struct device *dev)
{
	if (is_nd_btt(dev))
		nvdimm_namespace_detach_btt(to_nd_btt(dev));
	return 0;
}