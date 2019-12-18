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
struct ras_common_if {size_t block; } ;
struct ras_manager {int /*<<< orphan*/  node; struct amdgpu_device* adev; struct ras_common_if head; } ;
struct amdgpu_ras {int /*<<< orphan*/  head; struct ras_manager* objs; } ;
struct amdgpu_device {int dummy; } ;

/* Variables and functions */
 size_t AMDGPU_RAS_BLOCK_COUNT ; 
 scalar_t__ alive_obj (struct ras_manager*) ; 
 struct amdgpu_ras* amdgpu_ras_get_context (struct amdgpu_device*) ; 
 int /*<<< orphan*/  get_obj (struct ras_manager*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct ras_manager *amdgpu_ras_create_obj(struct amdgpu_device *adev,
		struct ras_common_if *head)
{
	struct amdgpu_ras *con = amdgpu_ras_get_context(adev);
	struct ras_manager *obj;

	if (!con)
		return NULL;

	if (head->block >= AMDGPU_RAS_BLOCK_COUNT)
		return NULL;

	obj = &con->objs[head->block];
	/* already exist. return obj? */
	if (alive_obj(obj))
		return NULL;

	obj->head = *head;
	obj->adev = adev;
	list_add(&obj->node, &con->head);
	get_obj(obj);

	return obj;
}