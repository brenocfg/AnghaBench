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
struct meson_i2c {scalar_t__ num_tokens; scalar_t__* tokens; } ;

/* Variables and functions */

__attribute__((used)) static void meson_i2c_reset_tokens(struct meson_i2c *i2c)
{
	i2c->tokens[0] = 0;
	i2c->tokens[1] = 0;
	i2c->num_tokens = 0;
}