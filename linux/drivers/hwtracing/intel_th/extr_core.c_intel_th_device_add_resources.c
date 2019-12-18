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
struct resource {int dummy; } ;
struct intel_th_device {int num_resources; struct resource* resource; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct resource* kmemdup (struct resource*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int intel_th_device_add_resources(struct intel_th_device *thdev,
					 struct resource *res, int nres)
{
	struct resource *r;

	r = kmemdup(res, sizeof(*res) * nres, GFP_KERNEL);
	if (!r)
		return -ENOMEM;

	thdev->resource = r;
	thdev->num_resources = nres;

	return 0;
}