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
struct input_value {unsigned int member_0; unsigned int member_1; int member_2; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (struct input_value*) ; 
 int /*<<< orphan*/  input_pass_values (struct input_dev*,struct input_value*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void input_pass_event(struct input_dev *dev,
			     unsigned int type, unsigned int code, int value)
{
	struct input_value vals[] = { { type, code, value } };

	input_pass_values(dev, vals, ARRAY_SIZE(vals));
}