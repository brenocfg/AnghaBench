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
struct TYPE_2__ {int num_dig; int /*<<< orphan*/ ** afmt; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dce_v8_0_afmt_fini(struct amdgpu_device *adev)
{
	int i;

	for (i = 0; i < adev->mode_info.num_dig; i++) {
		kfree(adev->mode_info.afmt[i]);
		adev->mode_info.afmt[i] = NULL;
	}
}