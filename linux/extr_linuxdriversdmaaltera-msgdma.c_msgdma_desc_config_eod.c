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
struct msgdma_extended_desc {int /*<<< orphan*/  control; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGDMA_DESC_CTL_TR_COMP_IRQ ; 

__attribute__((used)) static void msgdma_desc_config_eod(struct msgdma_extended_desc *desc)
{
	desc->control |= MSGDMA_DESC_CTL_TR_COMP_IRQ;
}