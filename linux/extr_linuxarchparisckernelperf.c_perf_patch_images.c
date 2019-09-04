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

/* Variables and functions */

__attribute__((used)) static void perf_patch_images(void)
{
#if 0 /* FIXME!! */
/*
 * NOTE:  this routine is VERY specific to the current TLB image.
 * If the image is changed, this routine might also need to be changed.
 */
	extern void $i_itlb_miss_2_0();
	extern void $i_dtlb_miss_2_0();
	extern void PA2_0_iva();

	/*
	 * We can only use the lower 32-bits, the upper 32-bits should be 0
	 * anyway given this is in the kernel
	 */
	uint32_t itlb_addr  = (uint32_t)&($i_itlb_miss_2_0);
	uint32_t dtlb_addr  = (uint32_t)&($i_dtlb_miss_2_0);
	uint32_t IVAaddress = (uint32_t)&PA2_0_iva;

	if (perf_processor_interface == ONYX_INTF) {
		/* clear last 2 bytes */
		onyx_images[TLBMISS][15] &= 0xffffff00;
		/* set 2 bytes */
		onyx_images[TLBMISS][15] |= (0x000000ff&((dtlb_addr) >> 24));
		onyx_images[TLBMISS][16] = (dtlb_addr << 8)&0xffffff00;
		onyx_images[TLBMISS][17] = itlb_addr;

		/* clear last 2 bytes */
		onyx_images[TLBHANDMISS][15] &= 0xffffff00;
		/* set 2 bytes */
		onyx_images[TLBHANDMISS][15] |= (0x000000ff&((dtlb_addr) >> 24));
		onyx_images[TLBHANDMISS][16] = (dtlb_addr << 8)&0xffffff00;
		onyx_images[TLBHANDMISS][17] = itlb_addr;

		/* clear last 2 bytes */
		onyx_images[BIG_CPI][15] &= 0xffffff00;
		/* set 2 bytes */
		onyx_images[BIG_CPI][15] |= (0x000000ff&((dtlb_addr) >> 24));
		onyx_images[BIG_CPI][16] = (dtlb_addr << 8)&0xffffff00;
		onyx_images[BIG_CPI][17] = itlb_addr;

	    onyx_images[PANIC][15] &= 0xffffff00;  /* clear last 2 bytes */
	 	onyx_images[PANIC][15] |= (0x000000ff&((IVAaddress) >> 24)); /* set 2 bytes */
		onyx_images[PANIC][16] = (IVAaddress << 8)&0xffffff00;


	} else if (perf_processor_interface == CUDA_INTF) {
		/* Cuda interface */
		cuda_images[TLBMISS][16] =
			(cuda_images[TLBMISS][16]&0xffff0000) |
			((dtlb_addr >> 8)&0x0000ffff);
		cuda_images[TLBMISS][17] =
			((dtlb_addr << 24)&0xff000000) | ((itlb_addr >> 16)&0x000000ff);
		cuda_images[TLBMISS][18] = (itlb_addr << 16)&0xffff0000;

		cuda_images[TLBHANDMISS][16] =
			(cuda_images[TLBHANDMISS][16]&0xffff0000) |
			((dtlb_addr >> 8)&0x0000ffff);
		cuda_images[TLBHANDMISS][17] =
			((dtlb_addr << 24)&0xff000000) | ((itlb_addr >> 16)&0x000000ff);
		cuda_images[TLBHANDMISS][18] = (itlb_addr << 16)&0xffff0000;

		cuda_images[BIG_CPI][16] =
			(cuda_images[BIG_CPI][16]&0xffff0000) |
			((dtlb_addr >> 8)&0x0000ffff);
		cuda_images[BIG_CPI][17] =
			((dtlb_addr << 24)&0xff000000) | ((itlb_addr >> 16)&0x000000ff);
		cuda_images[BIG_CPI][18] = (itlb_addr << 16)&0xffff0000;
	} else {
		/* Unknown type */
	}
#endif
}