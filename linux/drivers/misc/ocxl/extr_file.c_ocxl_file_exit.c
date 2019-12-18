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

/* Variables and functions */
 int /*<<< orphan*/  OCXL_NUM_MINORS ; 
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  minors_idr ; 
 int /*<<< orphan*/  ocxl_class ; 
 int /*<<< orphan*/  ocxl_dev ; 
 int /*<<< orphan*/  unregister_chrdev_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ocxl_file_exit(void)
{
	class_destroy(ocxl_class);
	unregister_chrdev_region(ocxl_dev, OCXL_NUM_MINORS);
	idr_destroy(&minors_idr);
}