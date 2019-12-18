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
struct cma_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cma_deref_dev (struct cma_device*) ; 

__attribute__((used)) static void cma_configfs_params_put(struct cma_device *cma_dev)
{
	cma_deref_dev(cma_dev);
}