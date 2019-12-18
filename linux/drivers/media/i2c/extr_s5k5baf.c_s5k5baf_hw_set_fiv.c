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
typedef  int /*<<< orphan*/  u16 ;
struct s5k5baf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_P_MAX_FR_TIME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5k5baf_hw_sync_cfg (struct s5k5baf*) ; 
 int /*<<< orphan*/  s5k5baf_write (struct s5k5baf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5k5baf_hw_set_fiv(struct s5k5baf *state, u16 fiv)
{
	s5k5baf_write(state, REG_P_MAX_FR_TIME(0), fiv);
	s5k5baf_hw_sync_cfg(state);
}