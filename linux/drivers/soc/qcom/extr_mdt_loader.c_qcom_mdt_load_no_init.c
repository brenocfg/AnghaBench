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
struct firmware {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;

/* Variables and functions */
 int __qcom_mdt_load (struct device*,struct firmware const*,char const*,int,void*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int) ; 

int qcom_mdt_load_no_init(struct device *dev, const struct firmware *fw,
			  const char *firmware, int pas_id,
			  void *mem_region, phys_addr_t mem_phys,
			  size_t mem_size, phys_addr_t *reloc_base)
{
	return __qcom_mdt_load(dev, fw, firmware, pas_id, mem_region, mem_phys,
			       mem_size, reloc_base, false);
}