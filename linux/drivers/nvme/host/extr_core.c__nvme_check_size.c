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
struct nvme_write_zeroes_cmd {int dummy; } ;
struct nvme_smart_log {int dummy; } ;
struct nvme_rw_command {int dummy; } ;
struct nvme_lba_range_type {int dummy; } ;
struct nvme_identify {int dummy; } ;
struct nvme_id_ns {int dummy; } ;
struct nvme_id_ctrl {int dummy; } ;
struct nvme_get_log_page_command {int dummy; } ;
struct nvme_format_cmd {int dummy; } ;
struct nvme_features {int dummy; } ;
struct nvme_dsm_cmd {int dummy; } ;
struct nvme_download_firmware {int dummy; } ;
struct nvme_directive_cmd {int dummy; } ;
struct nvme_dbbuf {int dummy; } ;
struct nvme_common_command {int dummy; } ;
struct nvme_command {int dummy; } ;
struct nvme_abort_cmd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int NVME_IDENTIFY_DATA_SIZE ; 

__attribute__((used)) static inline void _nvme_check_size(void)
{
	BUILD_BUG_ON(sizeof(struct nvme_common_command) != 64);
	BUILD_BUG_ON(sizeof(struct nvme_rw_command) != 64);
	BUILD_BUG_ON(sizeof(struct nvme_identify) != 64);
	BUILD_BUG_ON(sizeof(struct nvme_features) != 64);
	BUILD_BUG_ON(sizeof(struct nvme_download_firmware) != 64);
	BUILD_BUG_ON(sizeof(struct nvme_format_cmd) != 64);
	BUILD_BUG_ON(sizeof(struct nvme_dsm_cmd) != 64);
	BUILD_BUG_ON(sizeof(struct nvme_write_zeroes_cmd) != 64);
	BUILD_BUG_ON(sizeof(struct nvme_abort_cmd) != 64);
	BUILD_BUG_ON(sizeof(struct nvme_get_log_page_command) != 64);
	BUILD_BUG_ON(sizeof(struct nvme_command) != 64);
	BUILD_BUG_ON(sizeof(struct nvme_id_ctrl) != NVME_IDENTIFY_DATA_SIZE);
	BUILD_BUG_ON(sizeof(struct nvme_id_ns) != NVME_IDENTIFY_DATA_SIZE);
	BUILD_BUG_ON(sizeof(struct nvme_lba_range_type) != 64);
	BUILD_BUG_ON(sizeof(struct nvme_smart_log) != 512);
	BUILD_BUG_ON(sizeof(struct nvme_dbbuf) != 64);
	BUILD_BUG_ON(sizeof(struct nvme_directive_cmd) != 64);
}