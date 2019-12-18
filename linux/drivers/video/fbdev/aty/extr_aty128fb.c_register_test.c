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
typedef  int u32 ;
struct aty128fb_par {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIOS_0_SCRATCH ; 
 int aty_ld_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aty_st_le32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int register_test(const struct aty128fb_par *par)
{
	u32 val;
	int flag = 0;

	val = aty_ld_le32(BIOS_0_SCRATCH);

	aty_st_le32(BIOS_0_SCRATCH, 0x55555555);
	if (aty_ld_le32(BIOS_0_SCRATCH) == 0x55555555) {
		aty_st_le32(BIOS_0_SCRATCH, 0xAAAAAAAA);

		if (aty_ld_le32(BIOS_0_SCRATCH) == 0xAAAAAAAA)
			flag = 1; 
	}

	aty_st_le32(BIOS_0_SCRATCH, val);	// restore value
	return flag;
}