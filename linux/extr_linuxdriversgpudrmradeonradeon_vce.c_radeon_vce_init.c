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
typedef  int uint8_t ;
struct TYPE_3__ {int fw_version; int /*<<< orphan*/ ** filp; int /*<<< orphan*/ * handles; int /*<<< orphan*/  vcpu_bo; int /*<<< orphan*/  gpu_addr; int /*<<< orphan*/  fb_version; int /*<<< orphan*/  idle_work; } ;
struct radeon_device {int family; TYPE_1__ vce; int /*<<< orphan*/  dev; TYPE_2__* vce_fw; } ;
struct TYPE_4__ {int size; char* data; } ;

/* Variables and functions */
#define  CHIP_ARUBA 137 
#define  CHIP_BONAIRE 136 
#define  CHIP_HAWAII 135 
#define  CHIP_KABINI 134 
#define  CHIP_KAVERI 133 
#define  CHIP_MULLINS 132 
#define  CHIP_OLAND 131 
#define  CHIP_PITCAIRN 130 
#define  CHIP_TAHITI 129 
#define  CHIP_VERDE 128 
 int /*<<< orphan*/  DRM_INFO (char*,int,int,int,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 char* FIRMWARE_BONAIRE ; 
 char* FIRMWARE_TAHITI ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_VRAM ; 
 int RADEON_MAX_VCE_HANDLES ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int radeon_bo_create (struct radeon_device*,unsigned long,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int radeon_bo_pin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int radeon_bo_reserve (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  radeon_bo_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_vce_idle_work_handler ; 
 int request_firmware (TYPE_2__**,char const*,int /*<<< orphan*/ ) ; 
 int sscanf (char const*,char*,int*,...) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 
 unsigned long vce_v1_0_bo_size (struct radeon_device*) ; 
 unsigned long vce_v2_0_bo_size (struct radeon_device*) ; 

int radeon_vce_init(struct radeon_device *rdev)
{
	static const char *fw_version = "[ATI LIB=VCEFW,";
	static const char *fb_version = "[ATI LIB=VCEFWSTATS,";
	unsigned long size;
	const char *fw_name, *c;
	uint8_t start, mid, end;
	int i, r;

	INIT_DELAYED_WORK(&rdev->vce.idle_work, radeon_vce_idle_work_handler);

	switch (rdev->family) {
	case CHIP_TAHITI:
	case CHIP_PITCAIRN:
	case CHIP_VERDE:
	case CHIP_OLAND:
	case CHIP_ARUBA:
		fw_name = FIRMWARE_TAHITI;
		break;

	case CHIP_BONAIRE:
	case CHIP_KAVERI:
	case CHIP_KABINI:
	case CHIP_HAWAII:
	case CHIP_MULLINS:
		fw_name = FIRMWARE_BONAIRE;
		break;

	default:
		return -EINVAL;
	}

	r = request_firmware(&rdev->vce_fw, fw_name, rdev->dev);
	if (r) {
		dev_err(rdev->dev, "radeon_vce: Can't load firmware \"%s\"\n",
			fw_name);
		return r;
	}

	/* search for firmware version */

	size = rdev->vce_fw->size - strlen(fw_version) - 9;
	c = rdev->vce_fw->data;
	for (;size > 0; --size, ++c)
		if (strncmp(c, fw_version, strlen(fw_version)) == 0)
			break;

	if (size == 0)
		return -EINVAL;

	c += strlen(fw_version);
	if (sscanf(c, "%2hhd.%2hhd.%2hhd]", &start, &mid, &end) != 3)
		return -EINVAL;

	/* search for feedback version */

	size = rdev->vce_fw->size - strlen(fb_version) - 3;
	c = rdev->vce_fw->data;
	for (;size > 0; --size, ++c)
		if (strncmp(c, fb_version, strlen(fb_version)) == 0)
			break;

	if (size == 0)
		return -EINVAL;

	c += strlen(fb_version);
	if (sscanf(c, "%2u]", &rdev->vce.fb_version) != 1)
		return -EINVAL;

	DRM_INFO("Found VCE firmware/feedback version %hhd.%hhd.%hhd / %d!\n",
		 start, mid, end, rdev->vce.fb_version);

	rdev->vce.fw_version = (start << 24) | (mid << 16) | (end << 8);

	/* we can only work with this fw version for now */
	if ((rdev->vce.fw_version != ((40 << 24) | (2 << 16) | (2 << 8))) &&
	    (rdev->vce.fw_version != ((50 << 24) | (0 << 16) | (1 << 8))) &&
	    (rdev->vce.fw_version != ((50 << 24) | (1 << 16) | (2 << 8))))
		return -EINVAL;

	/* allocate firmware, stack and heap BO */

	if (rdev->family < CHIP_BONAIRE)
		size = vce_v1_0_bo_size(rdev);
	else
		size = vce_v2_0_bo_size(rdev);
	r = radeon_bo_create(rdev, size, PAGE_SIZE, true,
			     RADEON_GEM_DOMAIN_VRAM, 0, NULL, NULL,
			     &rdev->vce.vcpu_bo);
	if (r) {
		dev_err(rdev->dev, "(%d) failed to allocate VCE bo\n", r);
		return r;
	}

	r = radeon_bo_reserve(rdev->vce.vcpu_bo, false);
	if (r) {
		radeon_bo_unref(&rdev->vce.vcpu_bo);
		dev_err(rdev->dev, "(%d) failed to reserve VCE bo\n", r);
		return r;
	}

	r = radeon_bo_pin(rdev->vce.vcpu_bo, RADEON_GEM_DOMAIN_VRAM,
			  &rdev->vce.gpu_addr);
	radeon_bo_unreserve(rdev->vce.vcpu_bo);
	if (r) {
		radeon_bo_unref(&rdev->vce.vcpu_bo);
		dev_err(rdev->dev, "(%d) VCE bo pin failed\n", r);
		return r;
	}

	for (i = 0; i < RADEON_MAX_VCE_HANDLES; ++i) {
		atomic_set(&rdev->vce.handles[i], 0);
		rdev->vce.filp[i] = NULL;
	}

	return 0;
}