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
struct fintek_8250 {int dummy; } ;

/* Variables and functions */
 int sio_read_reg (struct fintek_8250*,int) ; 
 int /*<<< orphan*/  sio_write_reg (struct fintek_8250*,int,int) ; 

__attribute__((used)) static void sio_write_mask_reg(struct fintek_8250 *pdata, u8 reg, u8 mask,
			       u8 data)
{
	u8 tmp;

	tmp = (sio_read_reg(pdata, reg) & ~mask) | (mask & data);
	sio_write_reg(pdata, reg, tmp);
}