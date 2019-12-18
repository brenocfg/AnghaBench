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
struct TYPE_2__ {scalar_t__ patchid; } ;
struct adreno_gpu {TYPE_1__ rev; } ;

/* Variables and functions */
 scalar_t__ adreno_is_a330 (struct adreno_gpu*) ; 

__attribute__((used)) static inline bool adreno_is_a330v2(struct adreno_gpu *gpu)
{
	return adreno_is_a330(gpu) && (gpu->rev.patchid > 0);
}