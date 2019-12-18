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
struct pm3_par {int dummy; } ;
struct fb_info {struct pm3_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM3FilterMode ; 
 int /*<<< orphan*/  PM3FilterModeSync ; 
 int /*<<< orphan*/  PM3OutFIFOWords ; 
 int /*<<< orphan*/  PM3OutputFifo ; 
 int /*<<< orphan*/  PM3Sync ; 
 scalar_t__ PM3Sync_Tag ; 
 scalar_t__ PM3_READ_REG (struct pm3_par*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM3_WAIT (struct pm3_par*,int) ; 
 int /*<<< orphan*/  PM3_WRITE_REG (struct pm3_par*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static int pm3fb_sync(struct fb_info *info)
{
	struct pm3_par *par = info->par;

	PM3_WAIT(par, 2);
	PM3_WRITE_REG(par, PM3FilterMode, PM3FilterModeSync);
	PM3_WRITE_REG(par, PM3Sync, 0);
	mb();
	do {
		while ((PM3_READ_REG(par, PM3OutFIFOWords)) == 0)
			cpu_relax();
	} while ((PM3_READ_REG(par, PM3OutputFifo)) != PM3Sync_Tag);

	return 0;
}