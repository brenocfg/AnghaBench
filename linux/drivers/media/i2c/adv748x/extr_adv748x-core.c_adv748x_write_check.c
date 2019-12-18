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
typedef  int /*<<< orphan*/  u8 ;
struct adv748x_state {int dummy; } ;

/* Variables and functions */
 int adv748x_write (struct adv748x_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adv748x_write_check(struct adv748x_state *state, u8 page, u8 reg,
			       u8 value, int *error)
{
	if (*error)
		return *error;

	*error = adv748x_write(state, page, reg, value);
	return *error;
}