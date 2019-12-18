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
struct resource {int /*<<< orphan*/  flags; scalar_t__ end; scalar_t__ start; } ;
struct pnp_dev {int /*<<< orphan*/  dev; } ;
typedef  scalar_t__ resource_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_BUSY ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,struct resource*,char*) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct resource* request_mem_region (scalar_t__,scalar_t__,char*) ; 
 struct resource* request_region (scalar_t__,scalar_t__,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static void reserve_range(struct pnp_dev *dev, struct resource *r, int port)
{
	char *regionid;
	const char *pnpid = dev_name(&dev->dev);
	resource_size_t start = r->start, end = r->end;
	struct resource *res;

	regionid = kmalloc(16, GFP_KERNEL);
	if (!regionid)
		return;

	snprintf(regionid, 16, "pnp %s", pnpid);
	if (port)
		res = request_region(start, end - start + 1, regionid);
	else
		res = request_mem_region(start, end - start + 1, regionid);
	if (res)
		res->flags &= ~IORESOURCE_BUSY;
	else
		kfree(regionid);

	/*
	 * Failures at this point are usually harmless. pci quirks for
	 * example do reserve stuff they know about too, so we may well
	 * have double reservations.
	 */
	dev_info(&dev->dev, "%pR %s reserved\n", r,
		 res ? "has been" : "could not be");
}