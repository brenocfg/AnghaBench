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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dump_data_reg; int /*<<< orphan*/  dump_addr_reg; } ;
struct ipr_ioa_cfg {TYPE_1__ regs; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipr_get_sis64_dump_data_section(struct ipr_ioa_cfg *ioa_cfg,
					   u32 start_addr,
					   __be32 *dest, u32 length_in_words)
{
	int i;

	for (i = 0; i < length_in_words; i++) {
		writel(start_addr+(i*4), ioa_cfg->regs.dump_addr_reg);
		*dest = cpu_to_be32(readl(ioa_cfg->regs.dump_data_reg));
		dest++;
	}

	return 0;
}