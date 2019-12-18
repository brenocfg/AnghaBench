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

/* Variables and functions */
 int /*<<< orphan*/  PM3RD_PaletteData ; 
 int /*<<< orphan*/  PM3RD_PaletteWriteAddress ; 
 int /*<<< orphan*/  PM3_WAIT (struct pm3_par*,int) ; 
 int /*<<< orphan*/  PM3_WRITE_REG (struct pm3_par*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static inline void pm3fb_set_color(struct pm3_par *par, unsigned char regno,
			unsigned char r, unsigned char g, unsigned char b)
{
	PM3_WAIT(par, 4);
	PM3_WRITE_REG(par, PM3RD_PaletteWriteAddress, regno);
	wmb();
	PM3_WRITE_REG(par, PM3RD_PaletteData, r);
	wmb();
	PM3_WRITE_REG(par, PM3RD_PaletteData, g);
	wmb();
	PM3_WRITE_REG(par, PM3RD_PaletteData, b);
	wmb();
}