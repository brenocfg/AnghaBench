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
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int shader_present; } ;
struct panfrost_device {TYPE_1__ features; } ;

/* Variables and functions */
 int /*<<< orphan*/  JS_AFFINITY_NEXT_HI (int) ; 
 int /*<<< orphan*/  JS_AFFINITY_NEXT_LO (int) ; 
 int /*<<< orphan*/  job_write (struct panfrost_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void panfrost_job_write_affinity(struct panfrost_device *pfdev,
					u32 requirements,
					int js)
{
	u64 affinity;

	/*
	 * Use all cores for now.
	 * Eventually we may need to support tiler only jobs and h/w with
	 * multiple (2) coherent core groups
	 */
	affinity = pfdev->features.shader_present;

	job_write(pfdev, JS_AFFINITY_NEXT_LO(js), affinity & 0xFFFFFFFF);
	job_write(pfdev, JS_AFFINITY_NEXT_HI(js), affinity >> 32);
}