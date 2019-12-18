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
struct TYPE_2__ {void* size_log2; void* num_segs; void* swap_size; void* size; void** bus_addr; } ;
struct ath10k_swap_code_seg_info {size_t* paddr; void** virt_address; TYPE_1__ seg_hw_info; } ;
struct ath10k {int /*<<< orphan*/  dev; } ;
typedef  size_t dma_addr_t ;

/* Variables and functions */
 size_t ATH10K_SWAP_CODE_SEG_BIN_LEN_MAX ; 
 size_t ATH10K_SWAP_CODE_SEG_NUM_SUPPORTED ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* __cpu_to_le32 (size_t) ; 
 int /*<<< orphan*/  ath10k_err (struct ath10k*,char*,size_t,size_t) ; 
 struct ath10k_swap_code_seg_info* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ ,size_t,size_t*,int /*<<< orphan*/ ) ; 
 size_t ilog2 (size_t) ; 
 size_t roundup (size_t,int) ; 

__attribute__((used)) static struct ath10k_swap_code_seg_info *
ath10k_swap_code_seg_alloc(struct ath10k *ar, size_t swap_bin_len)
{
	struct ath10k_swap_code_seg_info *seg_info;
	void *virt_addr;
	dma_addr_t paddr;

	swap_bin_len = roundup(swap_bin_len, 2);
	if (swap_bin_len > ATH10K_SWAP_CODE_SEG_BIN_LEN_MAX) {
		ath10k_err(ar, "refusing code swap bin because it is too big %zu > %d\n",
			   swap_bin_len, ATH10K_SWAP_CODE_SEG_BIN_LEN_MAX);
		return NULL;
	}

	seg_info = devm_kzalloc(ar->dev, sizeof(*seg_info), GFP_KERNEL);
	if (!seg_info)
		return NULL;

	virt_addr = dma_alloc_coherent(ar->dev, swap_bin_len, &paddr,
				       GFP_KERNEL);
	if (!virt_addr)
		return NULL;

	seg_info->seg_hw_info.bus_addr[0] = __cpu_to_le32(paddr);
	seg_info->seg_hw_info.size = __cpu_to_le32(swap_bin_len);
	seg_info->seg_hw_info.swap_size = __cpu_to_le32(swap_bin_len);
	seg_info->seg_hw_info.num_segs =
			__cpu_to_le32(ATH10K_SWAP_CODE_SEG_NUM_SUPPORTED);
	seg_info->seg_hw_info.size_log2 = __cpu_to_le32(ilog2(swap_bin_len));
	seg_info->virt_address[0] = virt_addr;
	seg_info->paddr[0] = paddr;

	return seg_info;
}