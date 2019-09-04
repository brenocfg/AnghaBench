#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vc4_crtc {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  reg; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  CRTC_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* crtc_regs ; 

__attribute__((used)) static void vc4_crtc_dump_regs(struct vc4_crtc *vc4_crtc)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(crtc_regs); i++) {
		DRM_INFO("0x%04x (%s): 0x%08x\n",
			 crtc_regs[i].reg, crtc_regs[i].name,
			 CRTC_READ(crtc_regs[i].reg));
	}
}