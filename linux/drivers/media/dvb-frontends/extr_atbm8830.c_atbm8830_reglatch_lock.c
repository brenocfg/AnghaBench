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
struct atbm_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG_READ_LATCH ; 
 int atbm8830_write_reg (struct atbm_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int atbm8830_reglatch_lock(struct atbm_state *priv, int lock)
{
	return atbm8830_write_reg(priv, REG_READ_LATCH, lock ? 1 : 0);
}