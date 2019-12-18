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
typedef  scalar_t__ u16 ;
struct broadsheetfb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  broadsheet_write_reg (struct broadsheetfb_par*,scalar_t__,int) ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void broadsheet_write_reg32(struct broadsheetfb_par *par, u16 reg,
					u32 data)
{
	broadsheet_write_reg(par, reg, cpu_to_le32(data) & 0xFFFF);
	broadsheet_write_reg(par, reg + 2, (cpu_to_le32(data) >> 16) & 0xFFFF);
}