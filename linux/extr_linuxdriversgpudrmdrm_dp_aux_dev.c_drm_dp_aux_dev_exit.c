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
 int /*<<< orphan*/  class_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_dev_major ; 
 int /*<<< orphan*/  drm_dp_aux_dev_class ; 
 int /*<<< orphan*/  unregister_chrdev (int /*<<< orphan*/ ,char*) ; 

void drm_dp_aux_dev_exit(void)
{
	unregister_chrdev(drm_dev_major, "aux");
	class_destroy(drm_dp_aux_dev_class);
}