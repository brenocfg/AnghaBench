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
struct pxa168_eth_private {int /*<<< orphan*/  htpr_dma; scalar_t__ htpr; TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HASH_ADDR_TABLE_SIZE ; 
 int /*<<< orphan*/  HTPR ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrl (struct pxa168_eth_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_hash_table(struct pxa168_eth_private *pep)
{
	/*
	 * Hardware expects CPU to build a hash table based on a predefined
	 * hash function and populate it based on hardware address. The
	 * location of the hash table is identified by 32-bit pointer stored
	 * in HTPR internal register. Two possible sizes exists for the hash
	 * table 8kB (256kB of DRAM required (4 x 64 kB banks)) and 1/2kB
	 * (16kB of DRAM required (4 x 4 kB banks)).We currently only support
	 * 1/2kB.
	 */
	/* TODO: Add support for 8kB hash table and alternative hash
	 * function.Driver can dynamically switch to them if the 1/2kB hash
	 * table is full.
	 */
	if (!pep->htpr) {
		pep->htpr = dma_alloc_coherent(pep->dev->dev.parent,
					       HASH_ADDR_TABLE_SIZE,
					       &pep->htpr_dma, GFP_KERNEL);
		if (!pep->htpr)
			return -ENOMEM;
	} else {
		memset(pep->htpr, 0, HASH_ADDR_TABLE_SIZE);
	}
	wrl(pep, HTPR, pep->htpr_dma);
	return 0;
}