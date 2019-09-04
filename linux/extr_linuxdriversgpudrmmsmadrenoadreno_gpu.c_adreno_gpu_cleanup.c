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
struct adreno_gpu {int /*<<< orphan*/  base; int /*<<< orphan*/ * fw; TYPE_1__* info; } ;
struct TYPE_2__ {int /*<<< orphan*/  fw; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msm_gpu_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (int /*<<< orphan*/ ) ; 

void adreno_gpu_cleanup(struct adreno_gpu *adreno_gpu)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(adreno_gpu->info->fw); i++)
		release_firmware(adreno_gpu->fw[i]);

	msm_gpu_cleanup(&adreno_gpu->base);
}