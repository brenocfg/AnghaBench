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
struct kpc_dma_descriptor {int /*<<< orphan*/ * acd; scalar_t__ DescSystemAddrMS; scalar_t__ DescSystemAddrLS; scalar_t__ DescControlFlags; scalar_t__ DescCardAddrMS; scalar_t__ DescBufferByteCount; scalar_t__ DescCardAddrLS; scalar_t__ DescUserControlMS; scalar_t__ DescUserControlLS; scalar_t__ DescStatusFlags; scalar_t__ DescStatusErrorFlags; scalar_t__ DescByteCount; } ;

/* Variables and functions */

void  clear_desc(struct kpc_dma_descriptor *desc)
{
	if (!desc)
		return;
	desc->DescByteCount         = 0;
	desc->DescStatusErrorFlags  = 0;
	desc->DescStatusFlags       = 0;
	desc->DescUserControlLS     = 0;
	desc->DescUserControlMS     = 0;
	desc->DescCardAddrLS        = 0;
	desc->DescBufferByteCount   = 0;
	desc->DescCardAddrMS        = 0;
	desc->DescControlFlags      = 0;
	desc->DescSystemAddrLS      = 0;
	desc->DescSystemAddrMS      = 0;
	desc->acd = NULL;
}