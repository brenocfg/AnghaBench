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
typedef  size_t uint32_t ;
struct gamma_coefficients {void** user_gamma; void** a3; void** a2; void** a1; void** a0; } ;
typedef  int int32_t ;

/* Variables and functions */
 size_t ARRAY_SIZE (void**) ; 
 void* dc_fixpt_from_fraction (int const,int) ; 

__attribute__((used)) static void build_coefficients(struct gamma_coefficients *coefficients, bool is_2_4)
{
	static const int32_t numerator01[] = { 31308, 180000};
	static const int32_t numerator02[] = { 12920, 4500};
	static const int32_t numerator03[] = { 55, 99};
	static const int32_t numerator04[] = { 55, 99};
	static const int32_t numerator05[] = { 2400, 2200};

	uint32_t i = 0;
	uint32_t index = is_2_4 == true ? 0:1;

	do {
		coefficients->a0[i] = dc_fixpt_from_fraction(
			numerator01[index], 10000000);
		coefficients->a1[i] = dc_fixpt_from_fraction(
			numerator02[index], 1000);
		coefficients->a2[i] = dc_fixpt_from_fraction(
			numerator03[index], 1000);
		coefficients->a3[i] = dc_fixpt_from_fraction(
			numerator04[index], 1000);
		coefficients->user_gamma[i] = dc_fixpt_from_fraction(
			numerator05[index], 1000);

		++i;
	} while (i != ARRAY_SIZE(coefficients->a0));
}