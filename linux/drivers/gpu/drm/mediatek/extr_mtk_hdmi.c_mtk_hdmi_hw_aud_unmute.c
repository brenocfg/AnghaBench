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
struct mtk_hdmi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ZERO ; 
 int /*<<< orphan*/  GRL_AUDIO_CFG ; 
 int /*<<< orphan*/  mtk_hdmi_clear_bits (struct mtk_hdmi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_hdmi_hw_aud_unmute(struct mtk_hdmi *hdmi)
{
	mtk_hdmi_clear_bits(hdmi, GRL_AUDIO_CFG, AUDIO_ZERO);
}