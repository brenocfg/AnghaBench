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
typedef  int u32 ;
struct isp116x {int /*<<< orphan*/  data_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  isp116x_delay (struct isp116x*,int) ; 
 scalar_t__ readw (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 isp116x_read_data32(struct isp116x *isp116x)
{
	u32 val;

	val = (u32) readw(isp116x->data_reg);
	isp116x_delay(isp116x, 150);
	val |= ((u32) readw(isp116x->data_reg)) << 16;
	isp116x_delay(isp116x, 150);
	return val;
}