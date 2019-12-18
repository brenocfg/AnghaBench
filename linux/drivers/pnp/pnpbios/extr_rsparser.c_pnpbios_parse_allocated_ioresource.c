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
struct pnp_dev {int dummy; } ;

/* Variables and functions */
 int IORESOURCE_DISABLED ; 
 int /*<<< orphan*/  pnp_add_io_resource (struct pnp_dev*,int,int,int) ; 

__attribute__((used)) static void pnpbios_parse_allocated_ioresource(struct pnp_dev *dev,
					       int start, int len)
{
	int flags = 0;
	int end = start + len - 1;

	if (len <= 0 || end >= 0x10003)
		flags |= IORESOURCE_DISABLED;

	pnp_add_io_resource(dev, start, end, flags);
}