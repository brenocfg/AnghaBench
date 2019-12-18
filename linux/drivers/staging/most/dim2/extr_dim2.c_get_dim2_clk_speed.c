#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_3__ {int /*<<< orphan*/  clk_speed; int /*<<< orphan*/  clock_speed; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 TYPE_1__* clk_mt ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_dim2_clk_speed(const char *clock_speed, u8 *val)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(clk_mt); i++) {
		if (!strcmp(clock_speed, clk_mt[i].clock_speed)) {
			*val = clk_mt[i].clk_speed;
			return 0;
		}
	}
	return -EINVAL;
}