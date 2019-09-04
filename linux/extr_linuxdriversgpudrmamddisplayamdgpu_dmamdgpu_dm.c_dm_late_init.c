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
struct amdgpu_device {int /*<<< orphan*/  ddev; } ;

/* Variables and functions */
 int detect_mst_link_for_all_connectors (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dm_late_init(void *handle)
{
	struct amdgpu_device *adev = (struct amdgpu_device *)handle;

	return detect_mst_link_for_all_connectors(adev->ddev);
}