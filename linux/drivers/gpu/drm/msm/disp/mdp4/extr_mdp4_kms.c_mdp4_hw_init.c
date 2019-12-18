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
typedef  int uint32_t ;
struct msm_kms {int dummy; } ;
struct mdp4_kms {int rev; int /*<<< orphan*/  clk; struct drm_device* dev; } ;
struct TYPE_2__ {int allow_fb_modifiers; } ;
struct drm_device {int /*<<< orphan*/  dev; TYPE_1__ mode_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int,int) ; 
 int /*<<< orphan*/  DMA_E ; 
 int /*<<< orphan*/  DMA_P ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int,int) ; 
 int ENXIO ; 
 int FIELD (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDP4_VERSION_MAJOR ; 
 int /*<<< orphan*/  MDP4_VERSION_MINOR ; 
 int /*<<< orphan*/  REG_MDP4_CS_CONTROLLER0 ; 
 int /*<<< orphan*/  REG_MDP4_CS_CONTROLLER1 ; 
 int /*<<< orphan*/  REG_MDP4_DMA_FETCH_CONFIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_MDP4_DMA_P_OP_MODE ; 
 int /*<<< orphan*/  REG_MDP4_DMA_S_OP_MODE ; 
 int /*<<< orphan*/  REG_MDP4_LAYERMIXER_IN_CFG ; 
 int /*<<< orphan*/  REG_MDP4_LAYERMIXER_IN_CFG_UPDATE_METHOD ; 
 int /*<<< orphan*/  REG_MDP4_OVLP_CSC_CONFIG (int) ; 
 int /*<<< orphan*/  REG_MDP4_PIPE_FETCH_CONFIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_MDP4_PIPE_OP_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_MDP4_PORTMAP_MODE ; 
 int /*<<< orphan*/  REG_MDP4_READ_CNFG ; 
 int /*<<< orphan*/  REG_MDP4_RESET_STATUS ; 
 int /*<<< orphan*/  REG_MDP4_VERSION ; 
 int /*<<< orphan*/  RGB1 ; 
 int /*<<< orphan*/  RGB2 ; 
 int /*<<< orphan*/  VG1 ; 
 int /*<<< orphan*/  VG2 ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp4_disable (struct mdp4_kms*) ; 
 int /*<<< orphan*/  mdp4_enable (struct mdp4_kms*) ; 
 int mdp4_read (struct mdp4_kms*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp4_write (struct mdp4_kms*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ ) ; 
 struct mdp4_kms* to_mdp4_kms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mdp_kms (struct msm_kms*) ; 

__attribute__((used)) static int mdp4_hw_init(struct msm_kms *kms)
{
	struct mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));
	struct drm_device *dev = mdp4_kms->dev;
	uint32_t version, major, minor, dmap_cfg, vg_cfg;
	unsigned long clk;
	int ret = 0;

	pm_runtime_get_sync(dev->dev);

	mdp4_enable(mdp4_kms);
	version = mdp4_read(mdp4_kms, REG_MDP4_VERSION);
	mdp4_disable(mdp4_kms);

	major = FIELD(version, MDP4_VERSION_MAJOR);
	minor = FIELD(version, MDP4_VERSION_MINOR);

	DBG("found MDP4 version v%d.%d", major, minor);

	if (major != 4) {
		DRM_DEV_ERROR(dev->dev, "unexpected MDP version: v%d.%d\n",
				major, minor);
		ret = -ENXIO;
		goto out;
	}

	mdp4_kms->rev = minor;

	if (mdp4_kms->rev > 1) {
		mdp4_write(mdp4_kms, REG_MDP4_CS_CONTROLLER0, 0x0707ffff);
		mdp4_write(mdp4_kms, REG_MDP4_CS_CONTROLLER1, 0x03073f3f);
	}

	mdp4_write(mdp4_kms, REG_MDP4_PORTMAP_MODE, 0x3);

	/* max read pending cmd config, 3 pending requests: */
	mdp4_write(mdp4_kms, REG_MDP4_READ_CNFG, 0x02222);

	clk = clk_get_rate(mdp4_kms->clk);

	if ((mdp4_kms->rev >= 1) || (clk >= 90000000)) {
		dmap_cfg = 0x47;     /* 16 bytes-burst x 8 req */
		vg_cfg = 0x47;       /* 16 bytes-burs x 8 req */
	} else {
		dmap_cfg = 0x27;     /* 8 bytes-burst x 8 req */
		vg_cfg = 0x43;       /* 16 bytes-burst x 4 req */
	}

	DBG("fetch config: dmap=%02x, vg=%02x", dmap_cfg, vg_cfg);

	mdp4_write(mdp4_kms, REG_MDP4_DMA_FETCH_CONFIG(DMA_P), dmap_cfg);
	mdp4_write(mdp4_kms, REG_MDP4_DMA_FETCH_CONFIG(DMA_E), dmap_cfg);

	mdp4_write(mdp4_kms, REG_MDP4_PIPE_FETCH_CONFIG(VG1), vg_cfg);
	mdp4_write(mdp4_kms, REG_MDP4_PIPE_FETCH_CONFIG(VG2), vg_cfg);
	mdp4_write(mdp4_kms, REG_MDP4_PIPE_FETCH_CONFIG(RGB1), vg_cfg);
	mdp4_write(mdp4_kms, REG_MDP4_PIPE_FETCH_CONFIG(RGB2), vg_cfg);

	if (mdp4_kms->rev >= 2)
		mdp4_write(mdp4_kms, REG_MDP4_LAYERMIXER_IN_CFG_UPDATE_METHOD, 1);
	mdp4_write(mdp4_kms, REG_MDP4_LAYERMIXER_IN_CFG, 0);

	/* disable CSC matrix / YUV by default: */
	mdp4_write(mdp4_kms, REG_MDP4_PIPE_OP_MODE(VG1), 0);
	mdp4_write(mdp4_kms, REG_MDP4_PIPE_OP_MODE(VG2), 0);
	mdp4_write(mdp4_kms, REG_MDP4_DMA_P_OP_MODE, 0);
	mdp4_write(mdp4_kms, REG_MDP4_DMA_S_OP_MODE, 0);
	mdp4_write(mdp4_kms, REG_MDP4_OVLP_CSC_CONFIG(1), 0);
	mdp4_write(mdp4_kms, REG_MDP4_OVLP_CSC_CONFIG(2), 0);

	if (mdp4_kms->rev > 1)
		mdp4_write(mdp4_kms, REG_MDP4_RESET_STATUS, 1);

	dev->mode_config.allow_fb_modifiers = true;

out:
	pm_runtime_put_sync(dev->dev);

	return ret;
}