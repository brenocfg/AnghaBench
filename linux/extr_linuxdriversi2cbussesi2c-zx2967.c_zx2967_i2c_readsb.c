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
struct zx2967_i2c {scalar_t__ reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  readsb (scalar_t__,void*,int) ; 

__attribute__((used)) static void zx2967_i2c_readsb(struct zx2967_i2c *i2c,
			      void *data, unsigned long reg, int len)
{
	readsb(i2c->reg_base + reg, data, len);
}