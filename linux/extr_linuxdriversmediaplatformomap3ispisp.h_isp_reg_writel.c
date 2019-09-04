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
typedef  scalar_t__ u32 ;
struct isp_device {scalar_t__* mmio_base; } ;
typedef  enum isp_mem_resources { ____Placeholder_isp_mem_resources } isp_mem_resources ;

/* Variables and functions */
 int /*<<< orphan*/  __raw_writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline
void isp_reg_writel(struct isp_device *isp, u32 reg_value,
		    enum isp_mem_resources isp_mmio_range, u32 reg_offset)
{
	__raw_writel(reg_value, isp->mmio_base[isp_mmio_range] + reg_offset);
}