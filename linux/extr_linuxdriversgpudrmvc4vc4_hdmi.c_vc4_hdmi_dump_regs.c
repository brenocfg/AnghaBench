#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct vc4_dev {int dummy; } ;
struct drm_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  reg; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HDMI_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HD_READ (int /*<<< orphan*/ ) ; 
 TYPE_1__* hd_regs ; 
 TYPE_1__* hdmi_regs ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 

__attribute__((used)) static void vc4_hdmi_dump_regs(struct drm_device *dev)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	int i;

	for (i = 0; i < ARRAY_SIZE(hdmi_regs); i++) {
		DRM_INFO("0x%04x (%s): 0x%08x\n",
			 hdmi_regs[i].reg, hdmi_regs[i].name,
			 HDMI_READ(hdmi_regs[i].reg));
	}
	for (i = 0; i < ARRAY_SIZE(hd_regs); i++) {
		DRM_INFO("0x%04x (%s): 0x%08x\n",
			 hd_regs[i].reg, hd_regs[i].name,
			 HD_READ(hd_regs[i].reg));
	}
}