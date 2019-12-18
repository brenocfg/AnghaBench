#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int texctrl; int /*<<< orphan*/  texaddr; } ;
struct TYPE_8__ {TYPE_1__ s3d; } ;
struct TYPE_9__ {TYPE_2__ state; } ;
typedef  TYPE_3__ drm_savage_private_t ;
struct TYPE_10__ {int /*<<< orphan*/  texaddr; int /*<<< orphan*/  texctrl; int /*<<< orphan*/  new_scend; int /*<<< orphan*/  new_scstart; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int,unsigned int) ; 
 int EINVAL ; 
 unsigned int SAVAGE_DESTTEXRWWATERMARK_S3D ; 
 int /*<<< orphan*/  SAVAGE_SCEND_S3D ; 
 int /*<<< orphan*/  SAVAGE_SCISSOR_MASK_S3D ; 
 int /*<<< orphan*/  SAVAGE_SCSTART_S3D ; 
 unsigned int SAVAGE_TEXADDR_S3D ; 
 unsigned int SAVAGE_TEXCTRL_S3D ; 
 int SAVAGE_TEXCTRL_TEXEN_MASK ; 
 unsigned int SAVAGE_TEXPALADDR_S3D ; 
 int /*<<< orphan*/  SAVE_STATE (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAVE_STATE_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ s3d ; 
 int savage_verify_texaddr (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int savage_verify_state_s3d(drm_savage_private_t * dev_priv,
				   unsigned int start, unsigned int count,
				   const uint32_t *regs)
{
	if (start < SAVAGE_TEXPALADDR_S3D ||
	    start + count - 1 > SAVAGE_DESTTEXRWWATERMARK_S3D) {
		DRM_ERROR("invalid register range (0x%04x-0x%04x)\n",
			  start, start + count - 1);
		return -EINVAL;
	}

	SAVE_STATE_MASK(SAVAGE_SCSTART_S3D, s3d.new_scstart,
			~SAVAGE_SCISSOR_MASK_S3D);
	SAVE_STATE_MASK(SAVAGE_SCEND_S3D, s3d.new_scend,
			~SAVAGE_SCISSOR_MASK_S3D);

	/* if any texture regs were changed ... */
	if (start <= SAVAGE_TEXCTRL_S3D &&
	    start + count > SAVAGE_TEXPALADDR_S3D) {
		/* ... check texture state */
		SAVE_STATE(SAVAGE_TEXCTRL_S3D, s3d.texctrl);
		SAVE_STATE(SAVAGE_TEXADDR_S3D, s3d.texaddr);
		if (dev_priv->state.s3d.texctrl & SAVAGE_TEXCTRL_TEXEN_MASK)
			return savage_verify_texaddr(dev_priv, 0,
						dev_priv->state.s3d.texaddr);
	}

	return 0;
}