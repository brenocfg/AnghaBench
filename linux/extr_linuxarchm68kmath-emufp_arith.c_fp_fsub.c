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
struct fp_ext {int sign; } ;

/* Variables and functions */
 int /*<<< orphan*/  PINSTR ; 
 int /*<<< orphan*/  dprint (int /*<<< orphan*/ ,char*) ; 
 struct fp_ext* fp_fadd (struct fp_ext*,struct fp_ext*) ; 

struct fp_ext *
fp_fsub(struct fp_ext *dest, struct fp_ext *src)
{
	dprint(PINSTR, "fsub ");

	src->sign = !src->sign;
	return fp_fadd(dest, src);
}