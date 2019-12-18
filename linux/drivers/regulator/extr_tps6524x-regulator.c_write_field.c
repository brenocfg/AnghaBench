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
struct tps6524x {int dummy; } ;
struct field {int mask; int shift; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int EOVERFLOW ; 
 int rmw_protect (struct tps6524x*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int write_field(struct tps6524x *hw, const struct field *field,
		       int val)
{
	if (val & ~field->mask)
		return -EOVERFLOW;

	return rmw_protect(hw, field->reg,
				    field->mask << field->shift,
				    val << field->shift);
}