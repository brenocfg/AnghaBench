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
struct ib_device {int dummy; } ;
struct cma_device {struct ib_device* device; } ;

/* Variables and functions */

struct ib_device *cma_get_ib_dev(struct cma_device *cma_dev)
{
	return cma_dev->device;
}