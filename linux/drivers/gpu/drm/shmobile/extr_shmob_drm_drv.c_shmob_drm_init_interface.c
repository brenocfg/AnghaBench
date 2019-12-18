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
typedef  int u32 ;
struct shmob_drm_device {int ldmt1r; TYPE_2__* pdata; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {size_t interface; } ;
struct TYPE_4__ {TYPE_1__ iface; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int const*) ; 
 int EINVAL ; 
#define  LDMT1R_IFM 166 
#define  LDMT1R_MIFTYP_RGB12A 165 
#define  LDMT1R_MIFTYP_RGB12B 164 
#define  LDMT1R_MIFTYP_RGB16 163 
#define  LDMT1R_MIFTYP_RGB18 162 
#define  LDMT1R_MIFTYP_RGB24 161 
#define  LDMT1R_MIFTYP_RGB8 160 
#define  LDMT1R_MIFTYP_RGB9 159 
#define  LDMT1R_MIFTYP_SYS12 158 
#define  LDMT1R_MIFTYP_SYS16A 157 
#define  LDMT1R_MIFTYP_SYS16B 156 
#define  LDMT1R_MIFTYP_SYS16C 155 
#define  LDMT1R_MIFTYP_SYS18 154 
#define  LDMT1R_MIFTYP_SYS24 153 
#define  LDMT1R_MIFTYP_SYS8A 152 
#define  LDMT1R_MIFTYP_SYS8B 151 
#define  LDMT1R_MIFTYP_SYS8C 150 
#define  LDMT1R_MIFTYP_SYS8D 149 
#define  LDMT1R_MIFTYP_SYS9 148 
#define  LDMT1R_MIFTYP_YCBCR 147 
#define  SHMOB_DRM_IFACE_RGB12A 146 
#define  SHMOB_DRM_IFACE_RGB12B 145 
#define  SHMOB_DRM_IFACE_RGB16 144 
#define  SHMOB_DRM_IFACE_RGB18 143 
#define  SHMOB_DRM_IFACE_RGB24 142 
#define  SHMOB_DRM_IFACE_RGB8 141 
#define  SHMOB_DRM_IFACE_RGB9 140 
#define  SHMOB_DRM_IFACE_SYS12 139 
#define  SHMOB_DRM_IFACE_SYS16A 138 
#define  SHMOB_DRM_IFACE_SYS16B 137 
#define  SHMOB_DRM_IFACE_SYS16C 136 
#define  SHMOB_DRM_IFACE_SYS18 135 
#define  SHMOB_DRM_IFACE_SYS24 134 
#define  SHMOB_DRM_IFACE_SYS8A 133 
#define  SHMOB_DRM_IFACE_SYS8B 132 
#define  SHMOB_DRM_IFACE_SYS8C 131 
#define  SHMOB_DRM_IFACE_SYS8D 130 
#define  SHMOB_DRM_IFACE_SYS9 129 
#define  SHMOB_DRM_IFACE_YUV422 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static int shmob_drm_init_interface(struct shmob_drm_device *sdev)
{
	static const u32 ldmt1r[] = {
		[SHMOB_DRM_IFACE_RGB8] = LDMT1R_MIFTYP_RGB8,
		[SHMOB_DRM_IFACE_RGB9] = LDMT1R_MIFTYP_RGB9,
		[SHMOB_DRM_IFACE_RGB12A] = LDMT1R_MIFTYP_RGB12A,
		[SHMOB_DRM_IFACE_RGB12B] = LDMT1R_MIFTYP_RGB12B,
		[SHMOB_DRM_IFACE_RGB16] = LDMT1R_MIFTYP_RGB16,
		[SHMOB_DRM_IFACE_RGB18] = LDMT1R_MIFTYP_RGB18,
		[SHMOB_DRM_IFACE_RGB24] = LDMT1R_MIFTYP_RGB24,
		[SHMOB_DRM_IFACE_YUV422] = LDMT1R_MIFTYP_YCBCR,
		[SHMOB_DRM_IFACE_SYS8A] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS8A,
		[SHMOB_DRM_IFACE_SYS8B] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS8B,
		[SHMOB_DRM_IFACE_SYS8C] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS8C,
		[SHMOB_DRM_IFACE_SYS8D] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS8D,
		[SHMOB_DRM_IFACE_SYS9] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS9,
		[SHMOB_DRM_IFACE_SYS12] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS12,
		[SHMOB_DRM_IFACE_SYS16A] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS16A,
		[SHMOB_DRM_IFACE_SYS16B] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS16B,
		[SHMOB_DRM_IFACE_SYS16C] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS16C,
		[SHMOB_DRM_IFACE_SYS18] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS18,
		[SHMOB_DRM_IFACE_SYS24] = LDMT1R_IFM | LDMT1R_MIFTYP_SYS24,
	};

	if (sdev->pdata->iface.interface >= ARRAY_SIZE(ldmt1r)) {
		dev_err(sdev->dev, "invalid interface type %u\n",
			sdev->pdata->iface.interface);
		return -EINVAL;
	}

	sdev->ldmt1r = ldmt1r[sdev->pdata->iface.interface];
	return 0;
}