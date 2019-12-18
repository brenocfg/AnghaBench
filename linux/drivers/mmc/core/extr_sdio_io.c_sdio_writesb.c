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
struct sdio_func {int dummy; } ;

/* Variables and functions */
 int sdio_io_rw_ext_helper (struct sdio_func*,int,unsigned int,int /*<<< orphan*/ ,void*,int) ; 

int sdio_writesb(struct sdio_func *func, unsigned int addr, void *src,
	int count)
{
	return sdio_io_rw_ext_helper(func, 1, addr, 0, src, count);
}