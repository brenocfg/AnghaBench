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
struct s5k5baf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_PATTERN_HEIGHT ; 
 int /*<<< orphan*/  REG_PATTERN_PARAM ; 
 int /*<<< orphan*/  REG_PATTERN_SET ; 
 int /*<<< orphan*/  REG_PATTERN_WIDTH ; 
 int /*<<< orphan*/  s5k5baf_i2c_write (struct s5k5baf*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void s5k5baf_hw_set_test_pattern(struct s5k5baf *state, int id)
{
	s5k5baf_i2c_write(state, REG_PATTERN_WIDTH, 800);
	s5k5baf_i2c_write(state, REG_PATTERN_HEIGHT, 511);
	s5k5baf_i2c_write(state, REG_PATTERN_PARAM, 0);
	s5k5baf_i2c_write(state, REG_PATTERN_SET, id);
}