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
struct ff_device {int /*<<< orphan*/  ffbit; } ;

/* Variables and functions */
 int FF_PERIODIC ; 
 int FF_RUMBLE ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_compatible_type(struct ff_device *ff, int effect_type)
{

	if (test_bit(effect_type, ff->ffbit))
		return effect_type;

	if (effect_type == FF_PERIODIC && test_bit(FF_RUMBLE, ff->ffbit))
		return FF_RUMBLE;

	pr_err("invalid type in get_compatible_type()\n");

	return 0;
}