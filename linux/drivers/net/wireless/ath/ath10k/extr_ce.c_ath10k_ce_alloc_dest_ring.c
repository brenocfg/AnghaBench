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
typedef  int u32 ;
struct ce_desc {int dummy; } ;
struct ce_attr {int /*<<< orphan*/  dest_nentries; } ;
struct ath10k_ce_ring {int nentries; int nentries_mask; int /*<<< orphan*/  base_addr_ce_space_unaligned; int /*<<< orphan*/  base_addr_ce_space; int /*<<< orphan*/  base_addr_owner_space_unaligned; int /*<<< orphan*/  base_addr_owner_space; } ;
struct ath10k {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ CE_DESC_RING_ALIGN ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct ath10k_ce_ring* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PTR_ALIGN (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ath10k_ce_ring*) ; 
 struct ath10k_ce_ring* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  per_transfer_context ; 
 int roundup_pow_of_two (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  struct_size (struct ath10k_ce_ring*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ath10k_ce_ring *
ath10k_ce_alloc_dest_ring(struct ath10k *ar, unsigned int ce_id,
			  const struct ce_attr *attr)
{
	struct ath10k_ce_ring *dest_ring;
	u32 nentries;
	dma_addr_t base_addr;

	nentries = roundup_pow_of_two(attr->dest_nentries);

	dest_ring = kzalloc(struct_size(dest_ring, per_transfer_context,
					nentries), GFP_KERNEL);
	if (dest_ring == NULL)
		return ERR_PTR(-ENOMEM);

	dest_ring->nentries = nentries;
	dest_ring->nentries_mask = nentries - 1;

	/*
	 * Legacy platforms that do not support cache
	 * coherent DMA are unsupported
	 */
	dest_ring->base_addr_owner_space_unaligned =
		dma_alloc_coherent(ar->dev,
				   (nentries * sizeof(struct ce_desc) +
				    CE_DESC_RING_ALIGN),
				   &base_addr, GFP_KERNEL);
	if (!dest_ring->base_addr_owner_space_unaligned) {
		kfree(dest_ring);
		return ERR_PTR(-ENOMEM);
	}

	dest_ring->base_addr_ce_space_unaligned = base_addr;

	dest_ring->base_addr_owner_space =
			PTR_ALIGN(dest_ring->base_addr_owner_space_unaligned,
				  CE_DESC_RING_ALIGN);
	dest_ring->base_addr_ce_space =
				ALIGN(dest_ring->base_addr_ce_space_unaligned,
				      CE_DESC_RING_ALIGN);

	return dest_ring;
}