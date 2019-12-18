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
struct mfd_cell {void* platform_data; size_t pdata_size; int /*<<< orphan*/  name; } ;
struct mc13xxx {int /*<<< orphan*/  irq_data; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int E2BIG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kmemdup (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 char* mc13xxx_get_chipname (struct mc13xxx*) ; 
 int mfd_add_devices (int /*<<< orphan*/ ,int,struct mfd_cell*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_irq_get_domain (int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char const*,char const*) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static int mc13xxx_add_subdevice_pdata(struct mc13xxx *mc13xxx,
		const char *format, void *pdata, size_t pdata_size)
{
	char buf[30];
	const char *name = mc13xxx_get_chipname(mc13xxx);

	struct mfd_cell cell = {
		.platform_data = pdata,
		.pdata_size = pdata_size,
	};

	/* there is no asnprintf in the kernel :-( */
	if (snprintf(buf, sizeof(buf), format, name) > sizeof(buf))
		return -E2BIG;

	cell.name = kmemdup(buf, strlen(buf) + 1, GFP_KERNEL);
	if (!cell.name)
		return -ENOMEM;

	return mfd_add_devices(mc13xxx->dev, -1, &cell, 1, NULL, 0,
			       regmap_irq_get_domain(mc13xxx->irq_data));
}