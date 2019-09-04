#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_9__ ;
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  ucode_version; } ;
union amdgpu_firmware_header {TYPE_11__ common; } ;
typedef  int /*<<< orphan*/  uint16_t ;
struct kgd_dev {int dummy; } ;
struct TYPE_12__ {TYPE_9__* instance; } ;
struct TYPE_20__ {TYPE_6__* rlc_fw; TYPE_5__* mec2_fw; TYPE_4__* mec_fw; TYPE_3__* ce_fw; TYPE_2__* me_fw; TYPE_1__* pfp_fw; } ;
struct amdgpu_device {TYPE_10__ sdma; TYPE_7__ gfx; } ;
typedef  enum kgd_engine_type { ____Placeholder_kgd_engine_type } kgd_engine_type ;
struct TYPE_22__ {TYPE_8__* fw; } ;
struct TYPE_21__ {scalar_t__ data; } ;
struct TYPE_19__ {scalar_t__ data; } ;
struct TYPE_18__ {scalar_t__ data; } ;
struct TYPE_17__ {scalar_t__ data; } ;
struct TYPE_16__ {scalar_t__ data; } ;
struct TYPE_15__ {scalar_t__ data; } ;
struct TYPE_14__ {scalar_t__ data; } ;

/* Variables and functions */
#define  KGD_ENGINE_CE 135 
#define  KGD_ENGINE_ME 134 
#define  KGD_ENGINE_MEC1 133 
#define  KGD_ENGINE_MEC2 132 
#define  KGD_ENGINE_PFP 131 
#define  KGD_ENGINE_RLC 130 
#define  KGD_ENGINE_SDMA1 129 
#define  KGD_ENGINE_SDMA2 128 

__attribute__((used)) static uint16_t get_fw_version(struct kgd_dev *kgd, enum kgd_engine_type type)
{
	struct amdgpu_device *adev = (struct amdgpu_device *) kgd;
	const union amdgpu_firmware_header *hdr;

	switch (type) {
	case KGD_ENGINE_PFP:
		hdr = (const union amdgpu_firmware_header *)
						adev->gfx.pfp_fw->data;
		break;

	case KGD_ENGINE_ME:
		hdr = (const union amdgpu_firmware_header *)
						adev->gfx.me_fw->data;
		break;

	case KGD_ENGINE_CE:
		hdr = (const union amdgpu_firmware_header *)
						adev->gfx.ce_fw->data;
		break;

	case KGD_ENGINE_MEC1:
		hdr = (const union amdgpu_firmware_header *)
						adev->gfx.mec_fw->data;
		break;

	case KGD_ENGINE_MEC2:
		hdr = (const union amdgpu_firmware_header *)
						adev->gfx.mec2_fw->data;
		break;

	case KGD_ENGINE_RLC:
		hdr = (const union amdgpu_firmware_header *)
						adev->gfx.rlc_fw->data;
		break;

	case KGD_ENGINE_SDMA1:
		hdr = (const union amdgpu_firmware_header *)
						adev->sdma.instance[0].fw->data;
		break;

	case KGD_ENGINE_SDMA2:
		hdr = (const union amdgpu_firmware_header *)
						adev->sdma.instance[1].fw->data;
		break;

	default:
		return 0;
	}

	if (hdr == NULL)
		return 0;

	/* Only 12 bit in use*/
	return hdr->common.ucode_version;
}