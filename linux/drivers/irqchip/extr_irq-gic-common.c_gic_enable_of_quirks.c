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
struct gic_quirk {scalar_t__ desc; scalar_t__ (* init ) (void*) ;int /*<<< orphan*/  compatible; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_device_is_compatible (struct device_node const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,scalar_t__) ; 
 scalar_t__ stub1 (void*) ; 

void gic_enable_of_quirks(const struct device_node *np,
			  const struct gic_quirk *quirks, void *data)
{
	for (; quirks->desc; quirks++) {
		if (!of_device_is_compatible(np, quirks->compatible))
			continue;
		if (quirks->init(data))
			pr_info("GIC: enabling workaround for %s\n",
				quirks->desc);
	}
}