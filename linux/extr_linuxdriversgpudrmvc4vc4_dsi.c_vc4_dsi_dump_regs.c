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
struct vc4_dsi {scalar_t__ port; } ;
struct TYPE_4__ {int /*<<< orphan*/  reg; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  DRM_INFO (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSI_READ (int /*<<< orphan*/ ) ; 
 TYPE_1__* dsi0_regs ; 
 TYPE_1__* dsi1_regs ; 

__attribute__((used)) static void vc4_dsi_dump_regs(struct vc4_dsi *dsi)
{
	int i;

	if (dsi->port == 0) {
		for (i = 0; i < ARRAY_SIZE(dsi0_regs); i++) {
			DRM_INFO("0x%04x (%s): 0x%08x\n",
				 dsi0_regs[i].reg, dsi0_regs[i].name,
				 DSI_READ(dsi0_regs[i].reg));
		}
	} else {
		for (i = 0; i < ARRAY_SIZE(dsi1_regs); i++) {
			DRM_INFO("0x%04x (%s): 0x%08x\n",
				 dsi1_regs[i].reg, dsi1_regs[i].name,
				 DSI_READ(dsi1_regs[i].reg));
		}
	}
}