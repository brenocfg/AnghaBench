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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  atom_context; } ;
struct amdgpu_device {TYPE_1__ mode_info; } ;

/* Variables and functions */
 scalar_t__ amdgpu_atom_parse_cmd_header (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t bios_cmd_table_para_revision(void *dev,
					     uint32_t index)
{
	struct amdgpu_device *adev = dev;
	uint8_t frev, crev;

	if (amdgpu_atom_parse_cmd_header(adev->mode_info.atom_context,
					index,
					&frev, &crev))
		return crev;
	else
		return 0;
}