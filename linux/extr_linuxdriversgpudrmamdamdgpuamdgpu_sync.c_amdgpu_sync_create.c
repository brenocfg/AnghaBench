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
struct amdgpu_sync {int /*<<< orphan*/ * last_vm_update; int /*<<< orphan*/  fences; } ;

/* Variables and functions */
 int /*<<< orphan*/  hash_init (int /*<<< orphan*/ ) ; 

void amdgpu_sync_create(struct amdgpu_sync *sync)
{
	hash_init(sync->fences);
	sync->last_vm_update = NULL;
}