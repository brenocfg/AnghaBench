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
struct s5p_mfc_dev {int /*<<< orphan*/ * mem_dev; } ;

/* Variables and functions */
 size_t BANK_L_CTX ; 
 size_t BANK_R_CTX ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_dma_contig_clear_max_seg_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void s5p_mfc_unconfigure_2port_memory(struct s5p_mfc_dev *mfc_dev)
{
	device_unregister(mfc_dev->mem_dev[BANK_L_CTX]);
	device_unregister(mfc_dev->mem_dev[BANK_R_CTX]);
	vb2_dma_contig_clear_max_seg_size(mfc_dev->mem_dev[BANK_L_CTX]);
	vb2_dma_contig_clear_max_seg_size(mfc_dev->mem_dev[BANK_R_CTX]);
}