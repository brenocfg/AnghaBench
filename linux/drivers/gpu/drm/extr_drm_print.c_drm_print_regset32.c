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
struct drm_printer {int dummy; } ;
struct debugfs_regset32 {int nregs; TYPE_1__* regs; scalar_t__ base; } ;
struct TYPE_2__ {scalar_t__ offset; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_printf (struct drm_printer*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int max (int,int) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

void drm_print_regset32(struct drm_printer *p, struct debugfs_regset32 *regset)
{
	int namelen = 0;
	int i;

	for (i = 0; i < regset->nregs; i++)
		namelen = max(namelen, (int)strlen(regset->regs[i].name));

	for (i = 0; i < regset->nregs; i++) {
		drm_printf(p, "%*s = 0x%08x\n",
			   namelen, regset->regs[i].name,
			   readl(regset->base + regset->regs[i].offset));
	}
}