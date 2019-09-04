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
 int /*<<< orphan*/  REG_SF_USR_EXPOSURE_L ; 
 int /*<<< orphan*/  s5k5baf_write_seq (struct s5k5baf*,int /*<<< orphan*/ ,unsigned int,unsigned int,int) ; 

__attribute__((used)) static void s5k5baf_hw_set_user_exposure(struct s5k5baf *state, int exposure)
{
	unsigned int time = exposure / 10;

	s5k5baf_write_seq(state, REG_SF_USR_EXPOSURE_L,
			  time & 0xffff, time >> 16, 1);
}