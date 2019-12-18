#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct adv_dvc_var {int carrier_addr; TYPE_1__* carrier; TYPE_1__* carr_freelist; } ;
typedef  int off_t ;
typedef  int dma_addr_t ;
struct TYPE_2__ {void* next_vpa; scalar_t__ areq_vpa; void* carr_va; void* carr_pa; } ;
typedef  int /*<<< orphan*/  ADV_CARR_T ;

/* Variables and functions */
 int ADV_CARRIER_BUFSIZE ; 
 void* cpu_to_le32 (int) ; 

__attribute__((used)) static void AdvBuildCarrierFreelist(struct adv_dvc_var *adv_dvc)
{
	off_t carr_offset = 0, next_offset;
	dma_addr_t carr_paddr;
	int carr_num = ADV_CARRIER_BUFSIZE / sizeof(ADV_CARR_T), i;

	for (i = 0; i < carr_num; i++) {
		carr_offset = i * sizeof(ADV_CARR_T);
		/* Get physical address of the carrier 'carrp'. */
		carr_paddr = adv_dvc->carrier_addr + carr_offset;

		adv_dvc->carrier[i].carr_pa = cpu_to_le32(carr_paddr);
		adv_dvc->carrier[i].carr_va = cpu_to_le32(carr_offset);
		adv_dvc->carrier[i].areq_vpa = 0;
		next_offset = carr_offset + sizeof(ADV_CARR_T);
		if (i == carr_num)
			next_offset = ~0;
		adv_dvc->carrier[i].next_vpa = cpu_to_le32(next_offset);
	}
	/*
	 * We cannot have a carrier with 'carr_va' of '0', as
	 * a reference to this carrier would be interpreted as
	 * list termination.
	 * So start at carrier 1 with the freelist.
	 */
	adv_dvc->carr_freelist = &adv_dvc->carrier[1];
}