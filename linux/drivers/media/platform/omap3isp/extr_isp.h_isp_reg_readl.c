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
 scalar_t__ __raw_readl (scalar_t__) ; 

__attribute__((used)) static inline
u32 isp_reg_readl(struct isp_device *isp, enum isp_mem_resources isp_mmio_range,
		  u32 reg_offset)
{
	return __raw_readl(isp->mmio_base[isp_mmio_range] + reg_offset);
}