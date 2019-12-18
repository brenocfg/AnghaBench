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
struct brcmf_bus {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ENOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int brcmf_bus_get_memdump (struct brcmf_bus*,void*,size_t) ; 
 size_t brcmf_bus_get_ramsize (struct brcmf_bus*) ; 
 int /*<<< orphan*/  dev_coredumpv (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 void* vzalloc (size_t) ; 

int brcmf_debug_create_memdump(struct brcmf_bus *bus, const void *data,
			       size_t len)
{
	void *dump;
	size_t ramsize;
	int err;

	ramsize = brcmf_bus_get_ramsize(bus);
	if (!ramsize)
		return -ENOTSUPP;

	dump = vzalloc(len + ramsize);
	if (!dump)
		return -ENOMEM;

	if (data && len > 0)
		memcpy(dump, data, len);
	err = brcmf_bus_get_memdump(bus, dump + len, ramsize);
	if (err) {
		vfree(dump);
		return err;
	}

	dev_coredumpv(bus->dev, dump, len + ramsize, GFP_KERNEL);

	return 0;
}