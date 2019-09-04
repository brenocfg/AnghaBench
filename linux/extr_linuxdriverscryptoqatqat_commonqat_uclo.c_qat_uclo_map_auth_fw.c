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
typedef  int u64 ;
struct icp_qat_simg_ae_mode {int dummy; } ;
struct icp_qat_fw_loader_handle {int dummy; } ;
struct icp_qat_fw_auth_desc {int chunk_bus_addr; unsigned int css_hdr_high; unsigned int css_hdr_low; unsigned int fwsk_pub_high; unsigned int fwsk_pub_low; unsigned int signature_high; unsigned int signature_low; unsigned int img_high; unsigned int img_low; unsigned int img_len; unsigned int img_ae_mode_data_high; unsigned int img_ae_mode_data_low; unsigned int img_ae_init_data_high; unsigned int img_ae_init_data_low; unsigned int img_ae_insts_high; unsigned int img_ae_insts_low; int /*<<< orphan*/  chunk_size; } ;
struct icp_qat_css_hdr {scalar_t__ fw_type; } ;
struct icp_qat_auth_chunk {int chunk_bus_addr; unsigned int css_hdr_high; unsigned int css_hdr_low; unsigned int fwsk_pub_high; unsigned int fwsk_pub_low; unsigned int signature_high; unsigned int signature_low; unsigned int img_high; unsigned int img_low; unsigned int img_len; unsigned int img_ae_mode_data_high; unsigned int img_ae_mode_data_low; unsigned int img_ae_init_data_high; unsigned int img_ae_init_data_low; unsigned int img_ae_insts_high; unsigned int img_ae_insts_low; int /*<<< orphan*/  chunk_size; } ;
struct icp_firml_dram_desc {int dram_bus_addr; struct icp_qat_fw_auth_desc* dram_base_addr_v; int /*<<< orphan*/  dram_size; } ;

/* Variables and functions */
 int ADD_ADDR (unsigned int,unsigned int) ; 
 int BITS_IN_DWORD ; 
 scalar_t__ CSS_AE_FIRMWARE ; 
 int EINVAL ; 
 int ENOMEM ; 
 unsigned int ICP_QAT_AE_IMG_OFFSET ; 
 unsigned int ICP_QAT_CSS_AE_SIMG_LEN ; 
 int ICP_QAT_CSS_FWSK_EXPONENT_LEN ; 
 int ICP_QAT_CSS_FWSK_MODULUS_LEN ; 
 unsigned int ICP_QAT_CSS_FWSK_PAD_LEN ; 
 int ICP_QAT_CSS_FWSK_PUB_LEN ; 
 unsigned int ICP_QAT_CSS_MAX_IMAGE_LEN ; 
 int ICP_QAT_CSS_SIGNATURE_LEN ; 
 scalar_t__ ICP_QAT_SIMG_AE_INIT_SEQ_LEN ; 
 int /*<<< orphan*/  memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ qat_uclo_simg_alloc (struct icp_qat_fw_loader_handle*,struct icp_firml_dram_desc*,unsigned int) ; 

__attribute__((used)) static int qat_uclo_map_auth_fw(struct icp_qat_fw_loader_handle *handle,
				char *image, unsigned int size,
				struct icp_qat_fw_auth_desc **desc)
{
	struct icp_qat_css_hdr *css_hdr = (struct icp_qat_css_hdr *)image;
	struct icp_qat_fw_auth_desc *auth_desc;
	struct icp_qat_auth_chunk *auth_chunk;
	u64 virt_addr,  bus_addr, virt_base;
	unsigned int length, simg_offset = sizeof(*auth_chunk);
	struct icp_firml_dram_desc img_desc;

	if (size > (ICP_QAT_AE_IMG_OFFSET + ICP_QAT_CSS_MAX_IMAGE_LEN)) {
		pr_err("QAT: error, input image size overflow %d\n", size);
		return -EINVAL;
	}
	length = (css_hdr->fw_type == CSS_AE_FIRMWARE) ?
		 ICP_QAT_CSS_AE_SIMG_LEN + simg_offset :
		 size + ICP_QAT_CSS_FWSK_PAD_LEN + simg_offset;
	if (qat_uclo_simg_alloc(handle, &img_desc, length)) {
		pr_err("QAT: error, allocate continuous dram fail\n");
		return -ENOMEM;
	}

	auth_chunk = img_desc.dram_base_addr_v;
	auth_chunk->chunk_size = img_desc.dram_size;
	auth_chunk->chunk_bus_addr = img_desc.dram_bus_addr;
	virt_base = (uintptr_t)img_desc.dram_base_addr_v + simg_offset;
	bus_addr  = img_desc.dram_bus_addr + simg_offset;
	auth_desc = img_desc.dram_base_addr_v;
	auth_desc->css_hdr_high = (unsigned int)(bus_addr >> BITS_IN_DWORD);
	auth_desc->css_hdr_low = (unsigned int)bus_addr;
	virt_addr = virt_base;

	memcpy((void *)(uintptr_t)virt_addr, image, sizeof(*css_hdr));
	/* pub key */
	bus_addr = ADD_ADDR(auth_desc->css_hdr_high, auth_desc->css_hdr_low) +
			   sizeof(*css_hdr);
	virt_addr = virt_addr + sizeof(*css_hdr);

	auth_desc->fwsk_pub_high = (unsigned int)(bus_addr >> BITS_IN_DWORD);
	auth_desc->fwsk_pub_low = (unsigned int)bus_addr;

	memcpy((void *)(uintptr_t)virt_addr,
	       (void *)(image + sizeof(*css_hdr)),
	       ICP_QAT_CSS_FWSK_MODULUS_LEN);
	/* padding */
	memset((void *)(uintptr_t)(virt_addr + ICP_QAT_CSS_FWSK_MODULUS_LEN),
	       0, ICP_QAT_CSS_FWSK_PAD_LEN);

	/* exponent */
	memcpy((void *)(uintptr_t)(virt_addr + ICP_QAT_CSS_FWSK_MODULUS_LEN +
	       ICP_QAT_CSS_FWSK_PAD_LEN),
	       (void *)(image + sizeof(*css_hdr) +
			ICP_QAT_CSS_FWSK_MODULUS_LEN),
	       sizeof(unsigned int));

	/* signature */
	bus_addr = ADD_ADDR(auth_desc->fwsk_pub_high,
			    auth_desc->fwsk_pub_low) +
		   ICP_QAT_CSS_FWSK_PUB_LEN;
	virt_addr = virt_addr + ICP_QAT_CSS_FWSK_PUB_LEN;
	auth_desc->signature_high = (unsigned int)(bus_addr >> BITS_IN_DWORD);
	auth_desc->signature_low = (unsigned int)bus_addr;

	memcpy((void *)(uintptr_t)virt_addr,
	       (void *)(image + sizeof(*css_hdr) +
	       ICP_QAT_CSS_FWSK_MODULUS_LEN +
	       ICP_QAT_CSS_FWSK_EXPONENT_LEN),
	       ICP_QAT_CSS_SIGNATURE_LEN);

	bus_addr = ADD_ADDR(auth_desc->signature_high,
			    auth_desc->signature_low) +
		   ICP_QAT_CSS_SIGNATURE_LEN;
	virt_addr += ICP_QAT_CSS_SIGNATURE_LEN;

	auth_desc->img_high = (unsigned int)(bus_addr >> BITS_IN_DWORD);
	auth_desc->img_low = (unsigned int)bus_addr;
	auth_desc->img_len = size - ICP_QAT_AE_IMG_OFFSET;
	memcpy((void *)(uintptr_t)virt_addr,
	       (void *)(image + ICP_QAT_AE_IMG_OFFSET),
	       auth_desc->img_len);
	virt_addr = virt_base;
	/* AE firmware */
	if (((struct icp_qat_css_hdr *)(uintptr_t)virt_addr)->fw_type ==
	    CSS_AE_FIRMWARE) {
		auth_desc->img_ae_mode_data_high = auth_desc->img_high;
		auth_desc->img_ae_mode_data_low = auth_desc->img_low;
		bus_addr = ADD_ADDR(auth_desc->img_ae_mode_data_high,
				    auth_desc->img_ae_mode_data_low) +
			   sizeof(struct icp_qat_simg_ae_mode);

		auth_desc->img_ae_init_data_high = (unsigned int)
						 (bus_addr >> BITS_IN_DWORD);
		auth_desc->img_ae_init_data_low = (unsigned int)bus_addr;
		bus_addr += ICP_QAT_SIMG_AE_INIT_SEQ_LEN;
		auth_desc->img_ae_insts_high = (unsigned int)
					     (bus_addr >> BITS_IN_DWORD);
		auth_desc->img_ae_insts_low = (unsigned int)bus_addr;
	} else {
		auth_desc->img_ae_insts_high = auth_desc->img_high;
		auth_desc->img_ae_insts_low = auth_desc->img_low;
	}
	*desc = auth_desc;
	return 0;
}