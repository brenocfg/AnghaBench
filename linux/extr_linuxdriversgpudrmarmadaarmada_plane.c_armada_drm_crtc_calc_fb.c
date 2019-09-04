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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct drm_plane_state {int dummy; } ;
struct armada_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCD_CFG_GRA_PITCH ; 
 int /*<<< orphan*/  LCD_CFG_GRA_START_ADDR0 ; 
 int /*<<< orphan*/  LCD_CFG_GRA_START_ADDR1 ; 
 int /*<<< orphan*/  armada_drm_plane_calc (struct drm_plane_state*,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  armada_reg_queue_mod (struct armada_regs*,unsigned int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  armada_reg_queue_set (struct armada_regs*,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned armada_drm_crtc_calc_fb(struct drm_plane_state *state,
	struct armada_regs *regs, bool interlaced)
{
	u16 pitches[3];
	u32 addrs[2][3];
	unsigned i = 0;

	armada_drm_plane_calc(state, addrs, pitches, interlaced);

	/* write offset, base, and pitch */
	armada_reg_queue_set(regs, i, addrs[0][0], LCD_CFG_GRA_START_ADDR0);
	armada_reg_queue_set(regs, i, addrs[1][0], LCD_CFG_GRA_START_ADDR1);
	armada_reg_queue_mod(regs, i, pitches[0], 0xffff, LCD_CFG_GRA_PITCH);

	return i;
}