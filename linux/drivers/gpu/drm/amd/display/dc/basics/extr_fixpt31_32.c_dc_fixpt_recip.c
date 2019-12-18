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
struct fixed31_32 {int /*<<< orphan*/  value; } ;
struct TYPE_2__ {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 struct fixed31_32 dc_fixpt_from_fraction (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ dc_fixpt_one ; 

struct fixed31_32 dc_fixpt_recip(struct fixed31_32 arg)
{
	/*
	 * @note
	 * Good idea to use Newton's method
	 */

	ASSERT(arg.value);

	return dc_fixpt_from_fraction(
		dc_fixpt_one.value,
		arg.value);
}