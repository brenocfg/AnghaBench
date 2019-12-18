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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int /*<<< orphan*/  outb (int,scalar_t__) ; 
 int /*<<< orphan*/  outl (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void mlxcpld_i2c_lpc_write_buf(u8 *data, u8 len, u32 addr)
{
	int i;

	for (i = 0; i < len - len % 4; i += 4)
		outl(*(u32 *)(data + i), addr + i);
	for (; i < len; ++i)
		outb(*(data + i), addr + i);
}