#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dma_map_error; } ;
struct enic {TYPE_2__ gen_stats; TYPE_1__* netdev; int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  net_warn_ratelimited (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int enic_dma_map_check(struct enic *enic, dma_addr_t dma_addr)
{
	if (unlikely(pci_dma_mapping_error(enic->pdev, dma_addr))) {
		net_warn_ratelimited("%s: PCI dma mapping failed!\n",
				     enic->netdev->name);
		enic->gen_stats.dma_map_error++;

		return -ENOMEM;
	}

	return 0;
}