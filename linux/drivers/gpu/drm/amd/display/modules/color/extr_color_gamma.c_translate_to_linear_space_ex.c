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
struct gamma_coefficients {int /*<<< orphan*/ * user_gamma; int /*<<< orphan*/ * a3; int /*<<< orphan*/ * a2; int /*<<< orphan*/ * a1; int /*<<< orphan*/ * a0; } ;
struct fixed31_32 {int dummy; } ;

/* Variables and functions */
 struct fixed31_32 translate_to_linear_space (struct fixed31_32,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct fixed31_32 translate_to_linear_space_ex(
	struct fixed31_32 arg,
	struct gamma_coefficients *coeff,
	uint32_t color_index)
{
	return translate_to_linear_space(
		arg,
		coeff->a0[color_index],
		coeff->a1[color_index],
		coeff->a2[color_index],
		coeff->a3[color_index],
		coeff->user_gamma[color_index]);
}