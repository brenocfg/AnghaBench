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
struct cgs_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct cgs_device*) ; 

void amdgpu_cgs_destroy_device(struct cgs_device *cgs_device)
{
	kfree(cgs_device);
}