#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int fw_header_present; unsigned long max_handles; scalar_t__* img_size; int /*<<< orphan*/ ** filp; int /*<<< orphan*/ * handles; int /*<<< orphan*/  vcpu_bo; int /*<<< orphan*/  cpu_addr; int /*<<< orphan*/  gpu_addr; int /*<<< orphan*/  idle_work; } ;
struct radeon_device {int family; TYPE_1__ uvd; int /*<<< orphan*/  dev; TYPE_2__* uvd_fw; } ;
struct common_firmware_header {int /*<<< orphan*/  ucode_version; } ;
struct TYPE_5__ {scalar_t__ size; scalar_t__ data; } ;

/* Variables and functions */
#define  CHIP_ARUBA 160 
#define  CHIP_BARTS 159 
#define  CHIP_BONAIRE 158 
#define  CHIP_CAICOS 157 
#define  CHIP_CAYMAN 156 
#define  CHIP_CEDAR 155 
#define  CHIP_CYPRESS 154 
#define  CHIP_HAWAII 153 
#define  CHIP_HEMLOCK 152 
#define  CHIP_JUNIPER 151 
#define  CHIP_KABINI 150 
#define  CHIP_KAVERI 149 
#define  CHIP_MULLINS 148 
#define  CHIP_OLAND 147 
#define  CHIP_PALM 146 
#define  CHIP_PITCAIRN 145 
#define  CHIP_REDWOOD 144 
#define  CHIP_RS780 143 
#define  CHIP_RS880 142 
#define  CHIP_RV610 141 
#define  CHIP_RV620 140 
#define  CHIP_RV630 139 
#define  CHIP_RV635 138 
#define  CHIP_RV670 137 
#define  CHIP_RV710 136 
#define  CHIP_RV730 135 
#define  CHIP_RV740 134 
#define  CHIP_RV770 133 
#define  CHIP_SUMO 132 
#define  CHIP_SUMO2 131 
#define  CHIP_TAHITI 130 
#define  CHIP_TURKS 129 
#define  CHIP_VERDE 128 
 int /*<<< orphan*/  DRM_INFO (char*,unsigned int,unsigned int,unsigned int) ; 
 int EINVAL ; 
 char* FIRMWARE_BONAIRE ; 
 char* FIRMWARE_BONAIRE_LEGACY ; 
 char* FIRMWARE_CYPRESS ; 
 char* FIRMWARE_R600 ; 
 char* FIRMWARE_RS780 ; 
 char* FIRMWARE_RV710 ; 
 char* FIRMWARE_RV770 ; 
 char* FIRMWARE_SUMO ; 
 char* FIRMWARE_TAHITI ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 unsigned long RADEON_DEFAULT_UVD_HANDLES ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_VRAM ; 
 unsigned long RADEON_GPU_PAGE_ALIGN (scalar_t__) ; 
 unsigned long RADEON_MAX_UVD_HANDLES ; 
 unsigned long RADEON_UVD_HEAP_SIZE ; 
 unsigned long RADEON_UVD_SESSION_SIZE ; 
 unsigned long RADEON_UVD_STACK_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int radeon_bo_create (struct radeon_device*,unsigned long,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int radeon_bo_kmap (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int radeon_bo_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int radeon_bo_reserve (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_bo_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (int /*<<< orphan*/ ) ; 
 int radeon_ucode_validate (TYPE_2__*) ; 
 int /*<<< orphan*/  radeon_uvd_idle_work_handler ; 
 int request_firmware (TYPE_2__**,char const*,int /*<<< orphan*/ ) ; 

int radeon_uvd_init(struct radeon_device *rdev)
{
	unsigned long bo_size;
	const char *fw_name = NULL, *legacy_fw_name = NULL;
	int i, r;

	INIT_DELAYED_WORK(&rdev->uvd.idle_work, radeon_uvd_idle_work_handler);

	switch (rdev->family) {
	case CHIP_RV610:
	case CHIP_RV630:
	case CHIP_RV670:
	case CHIP_RV620:
	case CHIP_RV635:
		legacy_fw_name = FIRMWARE_R600;
		break;

	case CHIP_RS780:
	case CHIP_RS880:
		legacy_fw_name = FIRMWARE_RS780;
		break;

	case CHIP_RV770:
		legacy_fw_name = FIRMWARE_RV770;
		break;

	case CHIP_RV710:
	case CHIP_RV730:
	case CHIP_RV740:
		legacy_fw_name = FIRMWARE_RV710;
		break;

	case CHIP_CYPRESS:
	case CHIP_HEMLOCK:
	case CHIP_JUNIPER:
	case CHIP_REDWOOD:
	case CHIP_CEDAR:
		legacy_fw_name = FIRMWARE_CYPRESS;
		break;

	case CHIP_SUMO:
	case CHIP_SUMO2:
	case CHIP_PALM:
	case CHIP_CAYMAN:
	case CHIP_BARTS:
	case CHIP_TURKS:
	case CHIP_CAICOS:
		legacy_fw_name = FIRMWARE_SUMO;
		break;

	case CHIP_TAHITI:
	case CHIP_VERDE:
	case CHIP_PITCAIRN:
	case CHIP_ARUBA:
	case CHIP_OLAND:
		legacy_fw_name = FIRMWARE_TAHITI;
		break;

	case CHIP_BONAIRE:
	case CHIP_KABINI:
	case CHIP_KAVERI:
	case CHIP_HAWAII:
	case CHIP_MULLINS:
		legacy_fw_name = FIRMWARE_BONAIRE_LEGACY;
		fw_name = FIRMWARE_BONAIRE;
		break;

	default:
		return -EINVAL;
	}

	rdev->uvd.fw_header_present = false;
	rdev->uvd.max_handles = RADEON_DEFAULT_UVD_HANDLES;
	if (fw_name) {
		/* Let's try to load the newer firmware first */
		r = request_firmware(&rdev->uvd_fw, fw_name, rdev->dev);
		if (r) {
			dev_err(rdev->dev, "radeon_uvd: Can't load firmware \"%s\"\n",
				fw_name);
		} else {
			struct common_firmware_header *hdr = (void *)rdev->uvd_fw->data;
			unsigned version_major, version_minor, family_id;

			r = radeon_ucode_validate(rdev->uvd_fw);
			if (r)
				return r;

			rdev->uvd.fw_header_present = true;

			family_id = le32_to_cpu(hdr->ucode_version) & 0xff;
			version_major = (le32_to_cpu(hdr->ucode_version) >> 24) & 0xff;
			version_minor = (le32_to_cpu(hdr->ucode_version) >> 8) & 0xff;
			DRM_INFO("Found UVD firmware Version: %hu.%hu Family ID: %hu\n",
				 version_major, version_minor, family_id);

			/*
			 * Limit the number of UVD handles depending on
			 * microcode major and minor versions.
			 */
			if ((version_major >= 0x01) && (version_minor >= 0x37))
				rdev->uvd.max_handles = RADEON_MAX_UVD_HANDLES;
		}
	}

	/*
	 * In case there is only legacy firmware, or we encounter an error
	 * while loading the new firmware, we fall back to loading the legacy
	 * firmware now.
	 */
	if (!fw_name || r) {
		r = request_firmware(&rdev->uvd_fw, legacy_fw_name, rdev->dev);
		if (r) {
			dev_err(rdev->dev, "radeon_uvd: Can't load firmware \"%s\"\n",
				legacy_fw_name);
			return r;
		}
	}

	bo_size = RADEON_GPU_PAGE_ALIGN(rdev->uvd_fw->size + 8) +
		  RADEON_UVD_STACK_SIZE + RADEON_UVD_HEAP_SIZE +
		  RADEON_UVD_SESSION_SIZE * rdev->uvd.max_handles;
	r = radeon_bo_create(rdev, bo_size, PAGE_SIZE, true,
			     RADEON_GEM_DOMAIN_VRAM, 0, NULL,
			     NULL, &rdev->uvd.vcpu_bo);
	if (r) {
		dev_err(rdev->dev, "(%d) failed to allocate UVD bo\n", r);
		return r;
	}

	r = radeon_bo_reserve(rdev->uvd.vcpu_bo, false);
	if (r) {
		radeon_bo_unref(&rdev->uvd.vcpu_bo);
		dev_err(rdev->dev, "(%d) failed to reserve UVD bo\n", r);
		return r;
	}

	r = radeon_bo_pin(rdev->uvd.vcpu_bo, RADEON_GEM_DOMAIN_VRAM,
			  &rdev->uvd.gpu_addr);
	if (r) {
		radeon_bo_unreserve(rdev->uvd.vcpu_bo);
		radeon_bo_unref(&rdev->uvd.vcpu_bo);
		dev_err(rdev->dev, "(%d) UVD bo pin failed\n", r);
		return r;
	}

	r = radeon_bo_kmap(rdev->uvd.vcpu_bo, &rdev->uvd.cpu_addr);
	if (r) {
		dev_err(rdev->dev, "(%d) UVD map failed\n", r);
		return r;
	}

	radeon_bo_unreserve(rdev->uvd.vcpu_bo);

	for (i = 0; i < rdev->uvd.max_handles; ++i) {
		atomic_set(&rdev->uvd.handles[i], 0);
		rdev->uvd.filp[i] = NULL;
		rdev->uvd.img_size[i] = 0;
	}

	return 0;
}