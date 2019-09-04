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
struct mv_xor_desc_slot {int type; struct mv_xor_desc* hw_desc; } ;
struct mv_xor_desc {int /*<<< orphan*/  desc_command; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
#define  DMA_INTERRUPT 130 
#define  DMA_MEMCPY 129 
#define  DMA_XOR 128 
 int /*<<< orphan*/  XOR_DESC_OPERATION_MEMCPY ; 
 int /*<<< orphan*/  XOR_DESC_OPERATION_XOR ; 

__attribute__((used)) static void mv_desc_set_mode(struct mv_xor_desc_slot *desc)
{
	struct mv_xor_desc *hw_desc = desc->hw_desc;

	switch (desc->type) {
	case DMA_XOR:
	case DMA_INTERRUPT:
		hw_desc->desc_command |= XOR_DESC_OPERATION_XOR;
		break;
	case DMA_MEMCPY:
		hw_desc->desc_command |= XOR_DESC_OPERATION_MEMCPY;
		break;
	default:
		BUG();
		return;
	}
}