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
struct isert_device {int /*<<< orphan*/  pd; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dealloc_pd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isert_free_comps (struct isert_device*) ; 
 int /*<<< orphan*/  isert_info (char*,struct isert_device*) ; 

__attribute__((used)) static void
isert_free_device_ib_res(struct isert_device *device)
{
	isert_info("device %p\n", device);

	ib_dealloc_pd(device->pd);
	isert_free_comps(device);
}