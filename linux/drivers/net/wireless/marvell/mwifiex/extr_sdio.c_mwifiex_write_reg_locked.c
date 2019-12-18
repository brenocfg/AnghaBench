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
typedef  int /*<<< orphan*/  u32 ;
struct sdio_func {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sdio_writeb (struct sdio_func*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int
mwifiex_write_reg_locked(struct sdio_func *func, u32 reg, u8 data)
{
	int ret = -1;

	sdio_writeb(func, data, reg, &ret);
	return ret;
}