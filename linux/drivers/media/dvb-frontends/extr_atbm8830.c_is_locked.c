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
typedef  int u8 ;
struct atbm_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_LOCK_STATUS ; 
 int /*<<< orphan*/  atbm8830_read_reg (struct atbm_state*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int is_locked(struct atbm_state *priv, u8 *locked)
{
	u8 status;

	atbm8830_read_reg(priv, REG_LOCK_STATUS, &status);

	if (locked != NULL)
		*locked = (status == 1);
	return 0;
}