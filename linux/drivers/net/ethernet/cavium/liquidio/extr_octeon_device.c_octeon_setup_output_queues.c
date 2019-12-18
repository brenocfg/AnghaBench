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
typedef  size_t u32 ;
struct octeon_device {scalar_t__ num_oqs; int /*<<< orphan*/ ** droq; TYPE_1__* pci_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 size_t CFG_GET_DEF_RX_BUF_SIZE (int /*<<< orphan*/ ) ; 
 size_t CFG_GET_NUM_DEF_RX_DESCS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHIP_CONF (struct octeon_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ OCTEON_CN23XX_PF (struct octeon_device*) ; 
 scalar_t__ OCTEON_CN23XX_VF (struct octeon_device*) ; 
 scalar_t__ OCTEON_CN6XXX (struct octeon_device*) ; 
 int /*<<< orphan*/  cn23xx_pf ; 
 int /*<<< orphan*/  cn23xx_vf ; 
 int /*<<< orphan*/  cn6xxx ; 
 int dev_to_node (int /*<<< orphan*/ *) ; 
 scalar_t__ octeon_init_droq (struct octeon_device*,size_t,size_t,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vzalloc (int) ; 
 int /*<<< orphan*/ * vzalloc_node (int,int) ; 

int octeon_setup_output_queues(struct octeon_device *oct)
{
	u32 num_descs = 0;
	u32 desc_size = 0;
	u32 oq_no = 0;
	int numa_node = dev_to_node(&oct->pci_dev->dev);

	if (OCTEON_CN6XXX(oct)) {
		num_descs =
			CFG_GET_NUM_DEF_RX_DESCS(CHIP_CONF(oct, cn6xxx));
		desc_size =
			CFG_GET_DEF_RX_BUF_SIZE(CHIP_CONF(oct, cn6xxx));
	} else if (OCTEON_CN23XX_PF(oct)) {
		num_descs = CFG_GET_NUM_DEF_RX_DESCS(CHIP_CONF(oct, cn23xx_pf));
		desc_size = CFG_GET_DEF_RX_BUF_SIZE(CHIP_CONF(oct, cn23xx_pf));
	} else if (OCTEON_CN23XX_VF(oct)) {
		num_descs = CFG_GET_NUM_DEF_RX_DESCS(CHIP_CONF(oct, cn23xx_vf));
		desc_size = CFG_GET_DEF_RX_BUF_SIZE(CHIP_CONF(oct, cn23xx_vf));
	}
	oct->num_oqs = 0;
	oct->droq[0] = vzalloc_node(sizeof(*oct->droq[0]), numa_node);
	if (!oct->droq[0])
		oct->droq[0] = vzalloc(sizeof(*oct->droq[0]));
	if (!oct->droq[0])
		return 1;

	if (octeon_init_droq(oct, oq_no, num_descs, desc_size, NULL)) {
		vfree(oct->droq[oq_no]);
		oct->droq[oq_no] = NULL;
		return 1;
	}
	oct->num_oqs++;

	return 0;
}