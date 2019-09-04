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
struct platdata_mtd_ram {int /*<<< orphan*/  bankwidth; } ;
struct pismo_mem {int /*<<< orphan*/  width; } ;
struct pismo_data {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int pismo_add_device (struct pismo_data*,int,struct pismo_mem*,char*,struct platdata_mtd_ram*,int) ; 

__attribute__((used)) static int pismo_add_sram(struct pismo_data *pismo, int i,
			  struct pismo_mem *region)
{
	struct platdata_mtd_ram data = {
		.bankwidth = region->width,
	};

	return pismo_add_device(pismo, i, region, "mtd-ram",
		&data, sizeof(data));
}