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
struct be_mcc_wrb {int dummy; } ;
struct be_mcc_mailbox {struct be_mcc_wrb wrb; } ;
struct be_dma_mem {scalar_t__ va; } ;

/* Variables and functions */

struct be_mcc_wrb *wrb_from_mbox(struct be_dma_mem *mbox_mem)
{
	return &((struct be_mcc_mailbox *)(mbox_mem->va))->wrb;
}