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
struct v4l2_control {unsigned int member_0; unsigned int id; unsigned int value; int /*<<< orphan*/  const member_1; } ;
struct camif_dev {TYPE_2__* vp; TYPE_1__* variant; } ;
struct TYPE_4__ {int /*<<< orphan*/  offset; } ;
struct TYPE_3__ {scalar_t__ ip_revision; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct v4l2_control const*) ; 
#define  CIIMGEFF_FIN_ARBITRARY 141 
#define  CIIMGEFF_FIN_ARTFREEZE 140 
#define  CIIMGEFF_FIN_BYPASS 139 
#define  CIIMGEFF_FIN_EMBOSSING 138 
 unsigned int CIIMGEFF_FIN_MASK ; 
#define  CIIMGEFF_FIN_NEGATIVE 137 
#define  CIIMGEFF_FIN_SILHOUETTE 136 
 unsigned int CIIMGEFF_IE_ENABLE_MASK ; 
 unsigned int CIIMGEFF_PAT_CBCR_MASK ; 
 scalar_t__ S3C6400_CAMIF_IP_REV ; 
 int /*<<< orphan*/  S3C_CAMIF_REG_CIIMGEFF (int /*<<< orphan*/ ) ; 
#define  V4L2_COLORFX_ART_FREEZE 135 
#define  V4L2_COLORFX_BW 134 
#define  V4L2_COLORFX_EMBOSS 133 
#define  V4L2_COLORFX_NEGATIVE 132 
#define  V4L2_COLORFX_NONE 131 
#define  V4L2_COLORFX_SEPIA 130 
#define  V4L2_COLORFX_SET_CBCR 129 
#define  V4L2_COLORFX_SILHOUETTE 128 
 unsigned int camif_read (struct camif_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  camif_write (struct camif_dev*,int /*<<< orphan*/ ,unsigned int) ; 

void camif_hw_set_effect(struct camif_dev *camif, unsigned int effect,
			unsigned int cr, unsigned int cb)
{
	static const struct v4l2_control colorfx[] = {
		{ V4L2_COLORFX_NONE,		CIIMGEFF_FIN_BYPASS },
		{ V4L2_COLORFX_BW,		CIIMGEFF_FIN_ARBITRARY },
		{ V4L2_COLORFX_SEPIA,		CIIMGEFF_FIN_ARBITRARY },
		{ V4L2_COLORFX_NEGATIVE,	CIIMGEFF_FIN_NEGATIVE },
		{ V4L2_COLORFX_ART_FREEZE,	CIIMGEFF_FIN_ARTFREEZE },
		{ V4L2_COLORFX_EMBOSS,		CIIMGEFF_FIN_EMBOSSING },
		{ V4L2_COLORFX_SILHOUETTE,	CIIMGEFF_FIN_SILHOUETTE },
		{ V4L2_COLORFX_SET_CBCR,	CIIMGEFF_FIN_ARBITRARY },
	};
	unsigned int i, cfg;

	for (i = 0; i < ARRAY_SIZE(colorfx); i++)
		if (colorfx[i].id == effect)
			break;

	if (i == ARRAY_SIZE(colorfx))
		return;

	cfg = camif_read(camif, S3C_CAMIF_REG_CIIMGEFF(camif->vp->offset));
	/* Set effect */
	cfg &= ~CIIMGEFF_FIN_MASK;
	cfg |= colorfx[i].value;
	/* Set both paths */
	if (camif->variant->ip_revision >= S3C6400_CAMIF_IP_REV) {
		if (effect == V4L2_COLORFX_NONE)
			cfg &= ~CIIMGEFF_IE_ENABLE_MASK;
		else
			cfg |= CIIMGEFF_IE_ENABLE_MASK;
	}
	cfg &= ~CIIMGEFF_PAT_CBCR_MASK;
	cfg |= cr | (cb << 13);
	camif_write(camif, S3C_CAMIF_REG_CIIMGEFF(camif->vp->offset), cfg);
}