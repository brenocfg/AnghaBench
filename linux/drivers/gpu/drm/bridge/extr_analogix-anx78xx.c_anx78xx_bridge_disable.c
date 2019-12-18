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
struct drm_bridge {int dummy; } ;
struct anx78xx {int /*<<< orphan*/ * map; } ;

/* Variables and functions */
 size_t I2C_IDX_TX_P2 ; 
 int SP_AUDIO_PD ; 
 int SP_HDCP_PD ; 
 int SP_LINK_PD ; 
 int /*<<< orphan*/  SP_POWERDOWN_CTRL_REG ; 
 int SP_VIDEO_PD ; 
 int /*<<< orphan*/  anx78xx_set_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct anx78xx* bridge_to_anx78xx (struct drm_bridge*) ; 

__attribute__((used)) static void anx78xx_bridge_disable(struct drm_bridge *bridge)
{
	struct anx78xx *anx78xx = bridge_to_anx78xx(bridge);

	/* Power off all modules except configuration registers access */
	anx78xx_set_bits(anx78xx->map[I2C_IDX_TX_P2], SP_POWERDOWN_CTRL_REG,
			 SP_HDCP_PD | SP_AUDIO_PD | SP_VIDEO_PD | SP_LINK_PD);
}