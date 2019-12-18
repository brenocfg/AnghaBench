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
struct isp116x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  isp116x_read_data32 (struct isp116x*) ; 
 int /*<<< orphan*/  isp116x_write_addr (struct isp116x*,unsigned int) ; 

__attribute__((used)) static u32 isp116x_read_reg32(struct isp116x *isp116x, unsigned reg)
{
	isp116x_write_addr(isp116x, reg);
	return isp116x_read_data32(isp116x);
}