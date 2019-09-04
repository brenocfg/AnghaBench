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
struct sysc {scalar_t__ module_pa; scalar_t__* offsets; int /*<<< orphan*/  dev; } ;
struct resource {scalar_t__ start; } ;
typedef  enum sysc_registers { ____Placeholder_sysc_registers } sysc_registers ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ ENODEV ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
#define  SYSC_REVISION 130 
#define  SYSC_SYSCONFIG 129 
#define  SYSC_SYSSTATUS 128 
 struct resource* platform_get_resource_byname (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 char** reg_names ; 
 int /*<<< orphan*/  sysc_check_quirk_16bit (struct sysc*,struct resource*) ; 
 int /*<<< orphan*/  to_platform_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sysc_parse_one(struct sysc *ddata, enum sysc_registers reg)
{
	struct resource *res;
	const char *name;

	switch (reg) {
	case SYSC_REVISION:
	case SYSC_SYSCONFIG:
	case SYSC_SYSSTATUS:
		name = reg_names[reg];
		break;
	default:
		return -EINVAL;
	}

	res = platform_get_resource_byname(to_platform_device(ddata->dev),
					   IORESOURCE_MEM, name);
	if (!res) {
		ddata->offsets[reg] = -ENODEV;

		return 0;
	}

	ddata->offsets[reg] = res->start - ddata->module_pa;
	if (reg == SYSC_REVISION)
		sysc_check_quirk_16bit(ddata, res);

	return 0;
}