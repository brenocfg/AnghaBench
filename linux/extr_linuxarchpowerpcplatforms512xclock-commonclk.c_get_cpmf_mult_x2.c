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
struct TYPE_2__ {int /*<<< orphan*/  spmr; } ;

/* Variables and functions */
 TYPE_1__* clkregs ; 
 int get_bit_field (int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ soc_has_cpmf_0_bypass () ; 

__attribute__((used)) static int get_cpmf_mult_x2(void)
{
	static int cpmf_to_mult_x36[] = {
		/* 0b000 is "times 36" */
		72, 2, 2, 3, 4, 5, 6, 7,
	};
	static int cpmf_to_mult_0by[] = {
		/* 0b000 is "bypass" */
		2, 2, 2, 3, 4, 5, 6, 7,
	};

	int *cpmf_to_mult;
	int cpmf;

	cpmf = get_bit_field(&clkregs->spmr, 16, 4);
	if (soc_has_cpmf_0_bypass())
		cpmf_to_mult = cpmf_to_mult_0by;
	else
		cpmf_to_mult = cpmf_to_mult_x36;
	return cpmf_to_mult[cpmf];
}