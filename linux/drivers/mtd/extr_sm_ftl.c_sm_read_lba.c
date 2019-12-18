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
typedef  int uint32_t ;
typedef  int uint16_t ;
struct sm_oob {scalar_t__ lba_copy2; scalar_t__ lba_copy1; } ;

/* Variables and functions */
 int /*<<< orphan*/  SM_OOB_SIZE ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int /*<<< orphan*/  memcmp (struct sm_oob*,int const*,int /*<<< orphan*/ ) ; 
 int sm_get_lba (scalar_t__) ; 

__attribute__((used)) static int sm_read_lba(struct sm_oob *oob)
{
	static const uint32_t erased_pattern[4] = {
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

	uint16_t lba_test;
	int lba;

	/* First test for erased block */
	if (!memcmp(oob, erased_pattern, SM_OOB_SIZE))
		return -1;

	/* Now check is both copies of the LBA differ too much */
	lba_test = *(uint16_t *)oob->lba_copy1 ^ *(uint16_t*)oob->lba_copy2;
	if (lba_test && !is_power_of_2(lba_test))
		return -2;

	/* And read it */
	lba = sm_get_lba(oob->lba_copy1);

	if (lba == -2)
		lba = sm_get_lba(oob->lba_copy2);

	return lba;
}