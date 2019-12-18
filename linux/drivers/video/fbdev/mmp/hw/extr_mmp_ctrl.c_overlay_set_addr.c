#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* phys; } ;
struct mmp_overlay {TYPE_1__ addr; int /*<<< orphan*/  path; } ;
struct mmp_addr {int /*<<< orphan*/ * phys; } ;
struct lcd_regs {int /*<<< orphan*/  g_0; int /*<<< orphan*/  v_v0; int /*<<< orphan*/  v_u0; int /*<<< orphan*/  v_y0; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_1__*,struct mmp_addr*,int) ; 
 scalar_t__ overlay_is_vid (struct mmp_overlay*) ; 
 struct lcd_regs* path_regs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int overlay_set_addr(struct mmp_overlay *overlay, struct mmp_addr *addr)
{
	struct lcd_regs *regs = path_regs(overlay->path);

	/* FIXME: assert addr supported */
	memcpy(&overlay->addr, addr, sizeof(struct mmp_addr));

	if (overlay_is_vid(overlay)) {
		writel_relaxed(addr->phys[0], &regs->v_y0);
		writel_relaxed(addr->phys[1], &regs->v_u0);
		writel_relaxed(addr->phys[2], &regs->v_v0);
	} else
		writel_relaxed(addr->phys[0], &regs->g_0);

	return overlay->addr.phys[0];
}