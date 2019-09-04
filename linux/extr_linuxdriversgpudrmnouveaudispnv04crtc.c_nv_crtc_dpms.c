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
struct nouveau_drm {int dummy; } ;
struct nouveau_crtc {int last_dpms; int /*<<< orphan*/  index; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {struct drm_device* dev; } ;

/* Variables and functions */
#define  DRM_MODE_DPMS_OFF 131 
#define  DRM_MODE_DPMS_ON 130 
#define  DRM_MODE_DPMS_STANDBY 129 
#define  DRM_MODE_DPMS_SUSPEND 128 
 int NVReadVgaCrtc (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int NVReadVgaSeq (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVSetOwner (struct drm_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NVVgaSeqReset (struct drm_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NVWriteVgaCrtc (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  NVWriteVgaSeq (struct drm_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  NV_CIO_CRE_RPC1_INDEX ; 
 int /*<<< orphan*/  NV_CIO_CR_MODE_INDEX ; 
 int /*<<< orphan*/  NV_DEBUG (struct nouveau_drm*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NV_VIO_SR_CLOCK_INDEX ; 
 int /*<<< orphan*/  mdelay (int) ; 
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 
 struct nouveau_drm* nouveau_drm (struct drm_device*) ; 
 scalar_t__ nv_two_heads (struct drm_device*) ; 

__attribute__((used)) static void
nv_crtc_dpms(struct drm_crtc *crtc, int mode)
{
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	struct drm_device *dev = crtc->dev;
	struct nouveau_drm *drm = nouveau_drm(dev);
	unsigned char seq1 = 0, crtc17 = 0;
	unsigned char crtc1A;

	NV_DEBUG(drm, "Setting dpms mode %d on CRTC %d\n", mode,
							nv_crtc->index);

	if (nv_crtc->last_dpms == mode) /* Don't do unnecessary mode changes. */
		return;

	nv_crtc->last_dpms = mode;

	if (nv_two_heads(dev))
		NVSetOwner(dev, nv_crtc->index);

	/* nv4ref indicates these two RPC1 bits inhibit h/v sync */
	crtc1A = NVReadVgaCrtc(dev, nv_crtc->index,
					NV_CIO_CRE_RPC1_INDEX) & ~0xC0;
	switch (mode) {
	case DRM_MODE_DPMS_STANDBY:
		/* Screen: Off; HSync: Off, VSync: On -- Not Supported */
		seq1 = 0x20;
		crtc17 = 0x80;
		crtc1A |= 0x80;
		break;
	case DRM_MODE_DPMS_SUSPEND:
		/* Screen: Off; HSync: On, VSync: Off -- Not Supported */
		seq1 = 0x20;
		crtc17 = 0x80;
		crtc1A |= 0x40;
		break;
	case DRM_MODE_DPMS_OFF:
		/* Screen: Off; HSync: Off, VSync: Off */
		seq1 = 0x20;
		crtc17 = 0x00;
		crtc1A |= 0xC0;
		break;
	case DRM_MODE_DPMS_ON:
	default:
		/* Screen: On; HSync: On, VSync: On */
		seq1 = 0x00;
		crtc17 = 0x80;
		break;
	}

	NVVgaSeqReset(dev, nv_crtc->index, true);
	/* Each head has it's own sequencer, so we can turn it off when we want */
	seq1 |= (NVReadVgaSeq(dev, nv_crtc->index, NV_VIO_SR_CLOCK_INDEX) & ~0x20);
	NVWriteVgaSeq(dev, nv_crtc->index, NV_VIO_SR_CLOCK_INDEX, seq1);
	crtc17 |= (NVReadVgaCrtc(dev, nv_crtc->index, NV_CIO_CR_MODE_INDEX) & ~0x80);
	mdelay(10);
	NVWriteVgaCrtc(dev, nv_crtc->index, NV_CIO_CR_MODE_INDEX, crtc17);
	NVVgaSeqReset(dev, nv_crtc->index, false);

	NVWriteVgaCrtc(dev, nv_crtc->index, NV_CIO_CRE_RPC1_INDEX, crtc1A);
}