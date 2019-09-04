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
typedef  int /*<<< orphan*/  u32 ;
struct r592_device {scalar_t__ mmio; } ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_reg (char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 r592_read_reg_raw_be(struct r592_device *dev, int address)
{
	u32 value = __raw_readl(dev->mmio + address);
	dbg_reg("reg #%02d == 0x%08x", address, value);
	return be32_to_cpu(value);
}