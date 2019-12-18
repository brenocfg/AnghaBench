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
struct qla_hw_data {TYPE_1__* pdev; int /*<<< orphan*/  fw_attributes; int /*<<< orphan*/  fw_subminor_version; int /*<<< orphan*/  fw_minor_version; int /*<<< orphan*/  fw_major_version; } ;
struct qla2xxx_fw_dump {void* subsystem_device; void* subsystem_vendor; void* device; void* vendor; void* fw_attributes; void* fw_subminor_version; void* fw_minor_version; void* fw_major_version; } ;
struct TYPE_2__ {int /*<<< orphan*/  subsystem_device; int /*<<< orphan*/  subsystem_vendor; int /*<<< orphan*/  device; int /*<<< orphan*/  vendor; } ;

/* Variables and functions */
 void* htonl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
qla2xxx_prep_dump(struct qla_hw_data *ha, struct qla2xxx_fw_dump *fw_dump)
{
	fw_dump->fw_major_version = htonl(ha->fw_major_version);
	fw_dump->fw_minor_version = htonl(ha->fw_minor_version);
	fw_dump->fw_subminor_version = htonl(ha->fw_subminor_version);
	fw_dump->fw_attributes = htonl(ha->fw_attributes);

	fw_dump->vendor = htonl(ha->pdev->vendor);
	fw_dump->device = htonl(ha->pdev->device);
	fw_dump->subsystem_vendor = htonl(ha->pdev->subsystem_vendor);
	fw_dump->subsystem_device = htonl(ha->pdev->subsystem_device);
}