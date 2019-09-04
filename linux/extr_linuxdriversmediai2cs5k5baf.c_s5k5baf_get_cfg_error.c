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
typedef  scalar_t__ u16 ;
struct s5k5baf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_G_PREV_CFG_ERROR ; 
 scalar_t__ s5k5baf_read (struct s5k5baf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5k5baf_write (struct s5k5baf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u16 s5k5baf_get_cfg_error(struct s5k5baf *state)
{
	u16 err = s5k5baf_read(state, REG_G_PREV_CFG_ERROR);
	if (err)
		s5k5baf_write(state, REG_G_PREV_CFG_ERROR, 0);
	return err;
}