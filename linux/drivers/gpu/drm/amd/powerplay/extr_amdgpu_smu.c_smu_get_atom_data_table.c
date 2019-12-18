#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct smu_context {struct amdgpu_device* adev; } ;
struct TYPE_3__ {TYPE_2__* atom_context; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;
struct TYPE_4__ {scalar_t__ bios; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  amdgpu_atom_parse_data_header (TYPE_2__*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 

int smu_get_atom_data_table(struct smu_context *smu, uint32_t table,
			    uint16_t *size, uint8_t *frev, uint8_t *crev,
			    uint8_t **addr)
{
	struct amdgpu_device *adev = smu->adev;
	uint16_t data_start;

	if (!amdgpu_atom_parse_data_header(adev->mode_info.atom_context, table,
					   size, frev, crev, &data_start))
		return -EINVAL;

	*addr = (uint8_t *)adev->mode_info.atom_context->bios + data_start;

	return 0;
}