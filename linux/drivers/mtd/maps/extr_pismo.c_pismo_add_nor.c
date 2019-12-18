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
struct pismo_mem {int /*<<< orphan*/  width; } ;
struct pismo_data {scalar_t__ vpp; } ;
struct physmap_flash_data {int /*<<< orphan*/  set_vpp; int /*<<< orphan*/  width; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int pismo_add_device (struct pismo_data*,int,struct pismo_mem*,char*,struct physmap_flash_data*,int) ; 
 int /*<<< orphan*/  pismo_set_vpp ; 

__attribute__((used)) static int pismo_add_nor(struct pismo_data *pismo, int i,
			 struct pismo_mem *region)
{
	struct physmap_flash_data data = {
		.width = region->width,
	};

	if (pismo->vpp)
		data.set_vpp = pismo_set_vpp;

	return pismo_add_device(pismo, i, region, "physmap-flash",
		&data, sizeof(data));
}