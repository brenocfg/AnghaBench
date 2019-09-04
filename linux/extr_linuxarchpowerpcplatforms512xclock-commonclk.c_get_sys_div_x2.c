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
struct TYPE_2__ {int /*<<< orphan*/  scfr2; } ;

/* Variables and functions */
 TYPE_1__* clkregs ; 
 int get_bit_field (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int get_sys_div_x2(void)
{
	static int sysdiv_code_to_x2[] = {
		4, 5, 6, 7, 8, 9, 10, 14,
		12, 16, 18, 22, 20, 24, 26, 30,
		28, 32, 34, 38, 36, 40, 42, 46,
		44, 48, 50, 54, 52, 56, 58, 62,
		60, 64, 66,
	};
	int divcode;

	divcode = get_bit_field(&clkregs->scfr2, 26, 6);
	return sysdiv_code_to_x2[divcode];
}