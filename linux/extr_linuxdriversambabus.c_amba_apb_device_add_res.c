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
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct amba_device {int dummy; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 struct amba_device* amba_aphb_device_add (struct device*,char const*,int /*<<< orphan*/ ,size_t,int,int,void*,unsigned int,int /*<<< orphan*/ ,struct resource*) ; 

struct amba_device *
amba_apb_device_add_res(struct device *parent, const char *name,
			resource_size_t base, size_t size, int irq1,
			int irq2, void *pdata, unsigned int periphid,
			struct resource *resbase)
{
	return amba_aphb_device_add(parent, name, base, size, irq1, irq2, pdata,
				    periphid, 0, resbase);
}