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
typedef  int /*<<< orphan*/  u8 ;
struct mxl {TYPE_1__* base; } ;
struct TYPE_2__ {int /*<<< orphan*/  adr; int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int i2c_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int i2cwrite(struct mxl *state, u8 *data, int len)
{
	return i2c_write(state->base->i2c, state->base->adr, data, len);
}