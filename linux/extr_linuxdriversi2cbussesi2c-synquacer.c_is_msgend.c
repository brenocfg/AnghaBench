#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct synquacer_i2c {scalar_t__ msg_ptr; TYPE_1__* msg; } ;
struct TYPE_2__ {scalar_t__ len; } ;

/* Variables and functions */

__attribute__((used)) static inline int is_msgend(struct synquacer_i2c *i2c)
{
	return i2c->msg_ptr >= i2c->msg->len;
}