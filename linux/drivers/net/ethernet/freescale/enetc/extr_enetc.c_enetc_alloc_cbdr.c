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
struct enetc_cbdr {int bd_count; scalar_t__ next_to_use; scalar_t__ next_to_clean; int /*<<< orphan*/  bd_dma_base; int /*<<< orphan*/  bd_base; } ;
struct enetc_cbd {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enetc_alloc_cbdr(struct device *dev, struct enetc_cbdr *cbdr)
{
	int size = cbdr->bd_count * sizeof(struct enetc_cbd);

	cbdr->bd_base = dma_alloc_coherent(dev, size, &cbdr->bd_dma_base,
					   GFP_KERNEL);
	if (!cbdr->bd_base)
		return -ENOMEM;

	/* h/w requires 128B alignment */
	if (!IS_ALIGNED(cbdr->bd_dma_base, 128)) {
		dma_free_coherent(dev, size, cbdr->bd_base, cbdr->bd_dma_base);
		return -EINVAL;
	}

	cbdr->next_to_clean = 0;
	cbdr->next_to_use = 0;

	return 0;
}