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
typedef  size_t uint32_t ;
struct smu8_smumgr {scalar_t__ driver_buffer_length; TYPE_1__* driver_buffer; } ;
struct pp_hwmgr {int /*<<< orphan*/  device; struct smu8_smumgr* smu_backend; } ;
struct cgs_firmware_info {int /*<<< orphan*/  image_size; int /*<<< orphan*/  mc_addr; int /*<<< orphan*/  member_0; } ;
typedef  enum cgs_ucode_id { ____Placeholder_cgs_ucode_id } cgs_ucode_id ;
struct TYPE_2__ {int /*<<< orphan*/  firmware_ID; int /*<<< orphan*/  data_size; int /*<<< orphan*/  mc_addr; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int cgs_get_firmware_info (int /*<<< orphan*/ ,int,struct cgs_firmware_info*) ; 
 int /*<<< orphan*/ * firmware_list ; 
 int smu8_convert_fw_type_to_cgs (size_t) ; 
 size_t smu8_translate_firmware_enum_to_arg (struct pp_hwmgr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int smu8_smu_populate_firmware_entries(struct pp_hwmgr *hwmgr)
{
	struct smu8_smumgr *smu8_smu = hwmgr->smu_backend;
	uint32_t firmware_type;
	uint32_t i;
	int ret;
	enum cgs_ucode_id ucode_id;
	struct cgs_firmware_info info = {0};

	smu8_smu->driver_buffer_length = 0;

	for (i = 0; i < ARRAY_SIZE(firmware_list); i++) {

		firmware_type = smu8_translate_firmware_enum_to_arg(hwmgr,
					firmware_list[i]);

		ucode_id = smu8_convert_fw_type_to_cgs(firmware_type);

		ret = cgs_get_firmware_info(hwmgr->device,
							ucode_id, &info);

		if (ret == 0) {
			smu8_smu->driver_buffer[i].mc_addr = info.mc_addr;

			smu8_smu->driver_buffer[i].data_size = info.image_size;

			smu8_smu->driver_buffer[i].firmware_ID = firmware_list[i];
			smu8_smu->driver_buffer_length++;
		}
	}

	return 0;
}