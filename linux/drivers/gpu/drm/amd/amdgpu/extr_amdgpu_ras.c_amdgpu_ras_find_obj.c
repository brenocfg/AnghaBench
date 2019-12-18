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
struct TYPE_2__ {size_t block; } ;
struct ras_manager {TYPE_1__ head; } ;
struct ras_common_if {int block; } ;
struct amdgpu_ras {struct ras_manager* objs; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 int AMDGPU_RAS_BLOCK_COUNT ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ alive_obj (struct ras_manager*) ; 
 struct amdgpu_ras* amdgpu_ras_get_context (struct amdgpu_device*) ; 

__attribute__((used)) static struct ras_manager *amdgpu_ras_find_obj(struct amdgpu_device *adev,
		struct ras_common_if *head)
{
	struct amdgpu_ras *con = amdgpu_ras_get_context(adev);
	struct ras_manager *obj;
	int i;

	if (!con)
		return NULL;

	if (head) {
		if (head->block >= AMDGPU_RAS_BLOCK_COUNT)
			return NULL;

		obj = &con->objs[head->block];

		if (alive_obj(obj)) {
			WARN_ON(head->block != obj->head.block);
			return obj;
		}
	} else {
		for (i = 0; i < AMDGPU_RAS_BLOCK_COUNT; i++) {
			obj = &con->objs[i];
			if (alive_obj(obj)) {
				WARN_ON(i != obj->head.block);
				return obj;
			}
		}
	}

	return NULL;
}