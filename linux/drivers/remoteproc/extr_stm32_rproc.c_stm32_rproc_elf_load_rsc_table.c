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
struct rproc {int /*<<< orphan*/  dev; } ;
struct firmware {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ rproc_elf_load_rsc_table (struct rproc*,struct firmware const*) ; 

__attribute__((used)) static int stm32_rproc_elf_load_rsc_table(struct rproc *rproc,
					  const struct firmware *fw)
{
	if (rproc_elf_load_rsc_table(rproc, fw))
		dev_warn(&rproc->dev, "no resource table found for this firmware\n");

	return 0;
}