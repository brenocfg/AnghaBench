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
struct sdio_func {scalar_t__ tmpbuf; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int sdio_memcpy_toio (struct sdio_func*,unsigned int,scalar_t__,int) ; 

void sdio_writew(struct sdio_func *func, u16 b, unsigned int addr, int *err_ret)
{
	int ret;

	*(__le16 *)func->tmpbuf = cpu_to_le16(b);

	ret = sdio_memcpy_toio(func, addr, func->tmpbuf, 2);
	if (err_ret)
		*err_ret = ret;
}