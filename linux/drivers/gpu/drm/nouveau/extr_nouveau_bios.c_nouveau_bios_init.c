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
struct nvbios {int major_version; int execute; int is_mobile; } ;
struct nouveau_drm {struct nvbios vbios; } ;
struct drm_device {int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  NVInitVBIOS (struct drm_device*) ; 
 int NVReadVgaCrtc (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_CIO_CRE_4B ; 
 int /*<<< orphan*/  NV_INFO (struct nouveau_drm*,char*) ; 
 int /*<<< orphan*/  nouveau_bios_posted (struct drm_device*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 int nouveau_run_vbios_init (struct drm_device*) ; 
 int parse_dcb_table (struct drm_device*,struct nvbios*) ; 
 int parse_fp_mode_table (struct drm_device*,struct nvbios*) ; 

int
nouveau_bios_init(struct drm_device *dev)
{
	struct nouveau_drm *drm = nouveau_drm(dev);
	struct nvbios *bios = &drm->vbios;
	int ret;

	/* only relevant for PCI devices */
	if (!dev->pdev)
		return 0;

	if (!NVInitVBIOS(dev))
		return -ENODEV;

	ret = parse_dcb_table(dev, bios);
	if (ret)
		return ret;

	if (!bios->major_version)	/* we don't run version 0 bios */
		return 0;

	/* init script execution disabled */
	bios->execute = false;

	/* ... unless card isn't POSTed already */
	if (!nouveau_bios_posted(dev)) {
		NV_INFO(drm, "Adaptor not initialised, "
			"running VBIOS init tables.\n");
		bios->execute = true;
	}

	ret = nouveau_run_vbios_init(dev);
	if (ret)
		return ret;

	/* feature_byte on BMP is poor, but init always sets CR4B */
	if (bios->major_version < 5)
		bios->is_mobile = NVReadVgaCrtc(dev, 0, NV_CIO_CRE_4B) & 0x40;

	/* all BIT systems need p_f_m_t for digital_min_front_porch */
	if (bios->is_mobile || bios->major_version >= 5)
		ret = parse_fp_mode_table(dev, bios);

	/* allow subsequent scripts to execute */
	bios->execute = true;

	return 0;
}