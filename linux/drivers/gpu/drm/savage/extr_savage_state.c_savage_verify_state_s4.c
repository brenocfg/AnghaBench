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
struct TYPE_7__ {int texdescr; int /*<<< orphan*/  texaddr1; int /*<<< orphan*/  texaddr0; } ;
struct TYPE_8__ {TYPE_1__ s4; } ;
struct TYPE_9__ {TYPE_2__ state; } ;
typedef  TYPE_3__ drm_savage_private_t ;
struct TYPE_10__ {int /*<<< orphan*/  texaddr1; int /*<<< orphan*/  texaddr0; int /*<<< orphan*/  texdescr; int /*<<< orphan*/  new_drawctrl1; int /*<<< orphan*/  new_drawctrl0; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int,unsigned int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  SAVAGE_DRAWCTRL0_S4 ; 
 int /*<<< orphan*/  SAVAGE_DRAWCTRL1_S4 ; 
 unsigned int SAVAGE_DRAWLOCALCTRL_S4 ; 
 int /*<<< orphan*/  SAVAGE_SCISSOR_MASK_S4 ; 
 unsigned int SAVAGE_TEXADDR0_S4 ; 
 unsigned int SAVAGE_TEXADDR1_S4 ; 
 unsigned int SAVAGE_TEXBLENDCOLOR_S4 ; 
 unsigned int SAVAGE_TEXDESCR_S4 ; 
 int SAVAGE_TEXDESCR_TEX0EN_MASK ; 
 int SAVAGE_TEXDESCR_TEX1EN_MASK ; 
 unsigned int SAVAGE_TEXPALADDR_S4 ; 
 int /*<<< orphan*/  SAVE_STATE (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAVE_STATE_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ s4 ; 
 int savage_verify_texaddr (TYPE_3__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int savage_verify_state_s4(drm_savage_private_t * dev_priv,
				  unsigned int start, unsigned int count,
				  const uint32_t *regs)
{
	int ret = 0;

	if (start < SAVAGE_DRAWLOCALCTRL_S4 ||
	    start + count - 1 > SAVAGE_TEXBLENDCOLOR_S4) {
		DRM_ERROR("invalid register range (0x%04x-0x%04x)\n",
			  start, start + count - 1);
		return -EINVAL;
	}

	SAVE_STATE_MASK(SAVAGE_DRAWCTRL0_S4, s4.new_drawctrl0,
			~SAVAGE_SCISSOR_MASK_S4);
	SAVE_STATE_MASK(SAVAGE_DRAWCTRL1_S4, s4.new_drawctrl1,
			~SAVAGE_SCISSOR_MASK_S4);

	/* if any texture regs were changed ... */
	if (start <= SAVAGE_TEXDESCR_S4 &&
	    start + count > SAVAGE_TEXPALADDR_S4) {
		/* ... check texture state */
		SAVE_STATE(SAVAGE_TEXDESCR_S4, s4.texdescr);
		SAVE_STATE(SAVAGE_TEXADDR0_S4, s4.texaddr0);
		SAVE_STATE(SAVAGE_TEXADDR1_S4, s4.texaddr1);
		if (dev_priv->state.s4.texdescr & SAVAGE_TEXDESCR_TEX0EN_MASK)
			ret |= savage_verify_texaddr(dev_priv, 0,
						dev_priv->state.s4.texaddr0);
		if (dev_priv->state.s4.texdescr & SAVAGE_TEXDESCR_TEX1EN_MASK)
			ret |= savage_verify_texaddr(dev_priv, 1,
						dev_priv->state.s4.texaddr1);
	}

	return ret;
}