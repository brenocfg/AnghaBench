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
typedef  int /*<<< orphan*/  uint32_t ;
struct denali_nand_info {int max_banks; int revision; scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ FEATURES ; 
 int /*<<< orphan*/  FEATURES__N_BANKS ; 
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ioread32 (scalar_t__) ; 

__attribute__((used)) static void denali_detect_max_banks(struct denali_nand_info *denali)
{
	uint32_t features = ioread32(denali->reg + FEATURES);

	denali->max_banks = 1 << FIELD_GET(FEATURES__N_BANKS, features);

	/* the encoding changed from rev 5.0 to 5.1 */
	if (denali->revision < 0x0501)
		denali->max_banks <<= 1;
}