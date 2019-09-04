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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  FPU_REG ;

/* Variables and functions */
 int /*<<< orphan*/  FPU_normalize_nuo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setexponent16 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setnegative (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stdexp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u_char normalize_no_excep(FPU_REG *r, int exp, int sign)
{
	u_char tag;

	setexponent16(r, exp);

	tag = FPU_normalize_nuo(r);
	stdexp(r);
	if (sign)
		setnegative(r);

	return tag;
}