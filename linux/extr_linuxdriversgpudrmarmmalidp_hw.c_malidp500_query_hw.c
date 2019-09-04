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
typedef  int u8 ;
typedef  int u32 ;
struct malidp_hw_device {int min_line_size; int max_line_size; int* rotation_memory; } ;

/* Variables and functions */
 int /*<<< orphan*/  MALIDP500_CONFIG_ID ; 
 int SZ_1K ; 
 int SZ_2K ; 
 int malidp_hw_read (struct malidp_hw_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int malidp500_query_hw(struct malidp_hw_device *hwdev)
{
	u32 conf = malidp_hw_read(hwdev, MALIDP500_CONFIG_ID);
	/* bit 4 of the CONFIG_ID register holds the line size multiplier */
	u8 ln_size_mult = conf & 0x10 ? 2 : 1;

	hwdev->min_line_size = 2;
	hwdev->max_line_size = SZ_2K * ln_size_mult;
	hwdev->rotation_memory[0] = SZ_1K * 64 * ln_size_mult;
	hwdev->rotation_memory[1] = 0; /* no second rotation memory bank */

	return 0;
}