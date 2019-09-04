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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct ocrdma_dev {TYPE_1__ ibdev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ocrdma_attributes ; 

__attribute__((used)) static void ocrdma_remove_sysfiles(struct ocrdma_dev *dev)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(ocrdma_attributes); i++)
		device_remove_file(&dev->ibdev.dev, ocrdma_attributes[i]);
}