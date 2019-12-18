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
struct ocores_i2c {int /*<<< orphan*/  (* setreg ) (struct ocores_i2c*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct ocores_i2c*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void oc_setreg(struct ocores_i2c *i2c, int reg, u8 value)
{
	i2c->setreg(i2c, reg, value);
}