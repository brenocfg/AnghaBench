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
struct TYPE_2__ {int /*<<< orphan*/  sysdev; } ;
struct usb_hcd {void* localmem_pool; TYPE_1__ self; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (void*) ; 
 int /*<<< orphan*/  MEMREMAP_WC ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_to_node (int /*<<< orphan*/ ) ; 
 void* devm_gen_pool_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* devm_memremap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 
 int gen_pool_add_virt (void*,unsigned long,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

int usb_hcd_setup_local_mem(struct usb_hcd *hcd, phys_addr_t phys_addr,
			    dma_addr_t dma, size_t size)
{
	int err;
	void *local_mem;

	hcd->localmem_pool = devm_gen_pool_create(hcd->self.sysdev, 4,
						  dev_to_node(hcd->self.sysdev),
						  dev_name(hcd->self.sysdev));
	if (IS_ERR(hcd->localmem_pool))
		return PTR_ERR(hcd->localmem_pool);

	local_mem = devm_memremap(hcd->self.sysdev, phys_addr,
				  size, MEMREMAP_WC);
	if (IS_ERR(local_mem))
		return PTR_ERR(local_mem);

	/*
	 * Here we pass a dma_addr_t but the arg type is a phys_addr_t.
	 * It's not backed by system memory and thus there's no kernel mapping
	 * for it.
	 */
	err = gen_pool_add_virt(hcd->localmem_pool, (unsigned long)local_mem,
				dma, size, dev_to_node(hcd->self.sysdev));
	if (err < 0) {
		dev_err(hcd->self.sysdev, "gen_pool_add_virt failed with %d\n",
			err);
		return err;
	}

	return 0;
}