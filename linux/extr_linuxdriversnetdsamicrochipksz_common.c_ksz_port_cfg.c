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
struct ksz_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PORT_CTRL_ADDR (int,int) ; 
 int /*<<< orphan*/  ksz_read8 (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ksz_write8 (struct ksz_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ksz_port_cfg(struct ksz_device *dev, int port, int offset, u8 bits,
			 bool set)
{
	u32 addr;
	u8 data;

	addr = PORT_CTRL_ADDR(port, offset);
	ksz_read8(dev, addr, &data);

	if (set)
		data |= bits;
	else
		data &= ~bits;

	ksz_write8(dev, addr, data);
}