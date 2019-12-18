#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_9__ {scalar_t__ pp_table_id; } ;
struct TYPE_10__ {int power_play_table_size; void* power_play_table; TYPE_4__ boot_values; } ;
struct smu_context {TYPE_5__ smu_table; struct amdgpu_device* adev; } ;
struct TYPE_8__ {int /*<<< orphan*/  header_version_minor; int /*<<< orphan*/  header_version_major; } ;
struct smc_firmware_header_v1_0 {TYPE_3__ header; } ;
struct TYPE_7__ {TYPE_1__* fw; } ;
struct amdgpu_device {TYPE_2__ pm; } ;
struct TYPE_6__ {scalar_t__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  atom_master_list_of_data_tables_v2_1 ; 
 int get_index_into_master_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  powerplayinfo ; 
 int smu_get_atom_data_table (struct smu_context*,int,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int smu_v11_0_set_pptable_v2_0 (struct smu_context*,void**,int*) ; 
 int smu_v11_0_set_pptable_v2_1 (struct smu_context*,void**,int*,scalar_t__) ; 

__attribute__((used)) static int smu_v11_0_setup_pptable(struct smu_context *smu)
{
	struct amdgpu_device *adev = smu->adev;
	const struct smc_firmware_header_v1_0 *hdr;
	int ret, index;
	uint32_t size = 0;
	uint16_t atom_table_size;
	uint8_t frev, crev;
	void *table;
	uint16_t version_major, version_minor;

	hdr = (const struct smc_firmware_header_v1_0 *) adev->pm.fw->data;
	version_major = le16_to_cpu(hdr->header.header_version_major);
	version_minor = le16_to_cpu(hdr->header.header_version_minor);
	if (version_major == 2 && smu->smu_table.boot_values.pp_table_id > 0) {
		switch (version_minor) {
		case 0:
			ret = smu_v11_0_set_pptable_v2_0(smu, &table, &size);
			break;
		case 1:
			ret = smu_v11_0_set_pptable_v2_1(smu, &table, &size,
							 smu->smu_table.boot_values.pp_table_id);
			break;
		default:
			ret = -EINVAL;
			break;
		}
		if (ret)
			return ret;

	} else {
		index = get_index_into_master_table(atom_master_list_of_data_tables_v2_1,
						    powerplayinfo);

		ret = smu_get_atom_data_table(smu, index, &atom_table_size, &frev, &crev,
					      (uint8_t **)&table);
		if (ret)
			return ret;
		size = atom_table_size;
	}

	if (!smu->smu_table.power_play_table)
		smu->smu_table.power_play_table = table;
	if (!smu->smu_table.power_play_table_size)
		smu->smu_table.power_play_table_size = size;

	return 0;
}