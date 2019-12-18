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
struct etmv4_reg {scalar_t__ data; scalar_t__ addr; } ;
struct etmv4_drvdata {int /*<<< orphan*/  cpu; scalar_t__ base; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct etmv4_drvdata* dev_get_drvdata (struct device const*) ; 
 int /*<<< orphan*/  do_smp_cross_read ; 
 int /*<<< orphan*/  smp_call_function_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct etmv4_reg*,int) ; 

__attribute__((used)) static u32 etmv4_cross_read(const struct device *dev, u32 offset)
{
	struct etmv4_drvdata *drvdata = dev_get_drvdata(dev);
	struct etmv4_reg reg;

	reg.addr = drvdata->base + offset;
	/*
	 * smp cross call ensures the CPU will be powered up before
	 * accessing the ETMv4 trace core registers
	 */
	smp_call_function_single(drvdata->cpu, do_smp_cross_read, &reg, 1);
	return reg.data;
}