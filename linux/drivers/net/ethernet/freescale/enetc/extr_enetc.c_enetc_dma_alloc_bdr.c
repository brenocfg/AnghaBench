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
struct enetc_bdr {size_t bd_count; int /*<<< orphan*/  bd_dma_base; int /*<<< orphan*/  bd_base; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ALIGNED (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int enetc_dma_alloc_bdr(struct enetc_bdr *r, size_t bd_size)
{
	r->bd_base = dma_alloc_coherent(r->dev, r->bd_count * bd_size,
					&r->bd_dma_base, GFP_KERNEL);
	if (!r->bd_base)
		return -ENOMEM;

	/* h/w requires 128B alignment */
	if (!IS_ALIGNED(r->bd_dma_base, 128)) {
		dma_free_coherent(r->dev, r->bd_count * bd_size, r->bd_base,
				  r->bd_dma_base);
		return -EINVAL;
	}

	return 0;
}