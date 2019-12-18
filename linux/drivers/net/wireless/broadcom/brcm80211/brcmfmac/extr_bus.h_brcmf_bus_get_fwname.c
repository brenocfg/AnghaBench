#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct brcmf_bus {int /*<<< orphan*/  dev; TYPE_1__* ops; } ;
struct TYPE_2__ {int (* get_fwname ) (int /*<<< orphan*/ ,char const*,unsigned char*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,char const*,unsigned char*) ; 

__attribute__((used)) static inline
int brcmf_bus_get_fwname(struct brcmf_bus *bus, const char *ext,
			 unsigned char *fw_name)
{
	return bus->ops->get_fwname(bus->dev, ext, fw_name);
}