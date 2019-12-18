#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_13__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct imgu_fw_state_memory_offsets {int dummy; } ;
struct imgu_fw_param_memory_offsets {int dummy; } ;
struct TYPE_27__ {int* offsets; } ;
struct TYPE_15__ {int prog_name_offset; scalar_t__ size; scalar_t__ text_size; scalar_t__ icache_size; scalar_t__ data_size; scalar_t__ padding_size; int offset; TYPE_9__ memory_offsets; } ;
struct TYPE_23__ {scalar_t__ block_width; scalar_t__ output_block_height; } ;
struct TYPE_22__ {scalar_t__ num_stripes; } ;
struct TYPE_21__ {scalar_t__ mode; } ;
struct TYPE_24__ {TYPE_5__ block; TYPE_4__ iterator; TYPE_3__ pipeline; } ;
struct TYPE_25__ {scalar_t__ num_vf_formats; scalar_t__ num_output_formats; scalar_t__* output_formats; scalar_t__* vf_formats; TYPE_6__ sp; } ;
struct TYPE_20__ {scalar_t__ per_frame_data; scalar_t__ init_dmem_data; scalar_t__ host_sp_queue; scalar_t__ isp_started; scalar_t__ sw_state; scalar_t__ sleep_mode; scalar_t__ invalidate_tlb; scalar_t__ host_sp_com; scalar_t__ output; scalar_t__ host_sp_queues_initialized; } ;
struct TYPE_19__ {scalar_t__ sw_state; scalar_t__ num_dma_cmds; scalar_t__ dma_cmd_list; } ;
struct TYPE_26__ {TYPE_7__ isp; TYPE_2__ sp; TYPE_1__ bl; } ;
struct imgu_fw_info {scalar_t__ type; TYPE_10__ blob; TYPE_8__ info; } ;
struct TYPE_16__ {int h_size; int binary_nr; int /*<<< orphan*/  version; } ;
struct imgu_fw_header {struct imgu_fw_info* binary_header; TYPE_11__ file_header; } ;
struct imgu_fw_config_memory_offsets {int dummy; } ;
struct imgu_fw_bi_file_h {int dummy; } ;
struct imgu_device {int dummy; } ;
struct imgu_css {int fw_bl; int* fw_sp; scalar_t__ iomem_length; TYPE_12__* fw; TYPE_13__* binary; struct imgu_fw_header* fwp; struct device* dev; } ;
struct device {int dummy; } ;
struct TYPE_18__ {int /*<<< orphan*/  vaddr; } ;
struct TYPE_17__ {int size; scalar_t__ data; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IMGU_ABI_FRAME_FORMAT_NUM ; 
 size_t IMGU_ABI_MAX_BINARY_NAME ; 
 size_t IMGU_ABI_PARAM_CLASS_CONFIG ; 
 size_t IMGU_ABI_PARAM_CLASS_PARAM ; 
 size_t IMGU_ABI_PARAM_CLASS_STATE ; 
 scalar_t__ IMGU_FW_BOOTLOADER_FIRMWARE ; 
 scalar_t__ IMGU_FW_ISP_FIRMWARE ; 
 int /*<<< orphan*/  IMGU_FW_NAME ; 
 scalar_t__ IMGU_FW_SP1_FIRMWARE ; 
 scalar_t__ IMGU_FW_SP_FIRMWARE ; 
 scalar_t__ IPU3_CSS_PIPE_ID_NUM ; 
 scalar_t__ IPU3_UAPI_MAX_STRIPES ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct imgu_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,unsigned int,int) ; 
 int /*<<< orphan*/  imgu_css_fw_cleanup (struct imgu_css*) ; 
 int /*<<< orphan*/  imgu_css_fw_show_binary (struct device*,struct imgu_fw_info*,char const*) ; 
 int /*<<< orphan*/  imgu_dmamap_alloc (struct imgu_device*,TYPE_13__*,size_t) ; 
 TYPE_13__* kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void*,size_t) ; 
 int request_firmware (TYPE_12__**,int /*<<< orphan*/ ,struct device*) ; 
 size_t strnlen (char const*,int) ; 

int imgu_css_fw_init(struct imgu_css *css)
{
	static const u32 BLOCK_MAX = 65536;
	struct imgu_device *imgu = dev_get_drvdata(css->dev);
	struct device *dev = css->dev;
	unsigned int i, j, binary_nr;
	int r;

	r = request_firmware(&css->fw, IMGU_FW_NAME, css->dev);
	if (r)
		return r;

	/* Check and display fw header info */

	css->fwp = (struct imgu_fw_header *)css->fw->data;
	if (css->fw->size < sizeof(struct imgu_fw_header *) ||
	    css->fwp->file_header.h_size != sizeof(struct imgu_fw_bi_file_h))
		goto bad_fw;
	if (sizeof(struct imgu_fw_bi_file_h) +
	    css->fwp->file_header.binary_nr * sizeof(struct imgu_fw_info) >
	    css->fw->size)
		goto bad_fw;

	dev_info(dev, "loaded firmware version %.64s, %u binaries, %zu bytes\n",
		 css->fwp->file_header.version, css->fwp->file_header.binary_nr,
		 css->fw->size);

	/* Validate and display info on fw binaries */

	binary_nr = css->fwp->file_header.binary_nr;

	css->fw_bl = -1;
	css->fw_sp[0] = -1;
	css->fw_sp[1] = -1;

	for (i = 0; i < binary_nr; i++) {
		struct imgu_fw_info *bi = &css->fwp->binary_header[i];
		const char *name = (void *)css->fwp + bi->blob.prog_name_offset;
		size_t len;

		if (bi->blob.prog_name_offset >= css->fw->size)
			goto bad_fw;
		len = strnlen(name, css->fw->size - bi->blob.prog_name_offset);
		if (len + 1 > css->fw->size - bi->blob.prog_name_offset ||
		    len + 1 >= IMGU_ABI_MAX_BINARY_NAME)
			goto bad_fw;

		if (bi->blob.size != bi->blob.text_size + bi->blob.icache_size
		    + bi->blob.data_size + bi->blob.padding_size)
			goto bad_fw;
		if (bi->blob.offset + bi->blob.size > css->fw->size)
			goto bad_fw;

		if (bi->type == IMGU_FW_BOOTLOADER_FIRMWARE) {
			css->fw_bl = i;
			if (bi->info.bl.sw_state >= css->iomem_length ||
			    bi->info.bl.num_dma_cmds >= css->iomem_length ||
			    bi->info.bl.dma_cmd_list >= css->iomem_length)
				goto bad_fw;
		}
		if (bi->type == IMGU_FW_SP_FIRMWARE ||
		    bi->type == IMGU_FW_SP1_FIRMWARE) {
			css->fw_sp[bi->type == IMGU_FW_SP_FIRMWARE ? 0 : 1] = i;
			if (bi->info.sp.per_frame_data >= css->iomem_length ||
			    bi->info.sp.init_dmem_data >= css->iomem_length ||
			    bi->info.sp.host_sp_queue >= css->iomem_length ||
			    bi->info.sp.isp_started >= css->iomem_length ||
			    bi->info.sp.sw_state >= css->iomem_length ||
			    bi->info.sp.sleep_mode >= css->iomem_length ||
			    bi->info.sp.invalidate_tlb >= css->iomem_length ||
			    bi->info.sp.host_sp_com >= css->iomem_length ||
			    bi->info.sp.output + 12 >= css->iomem_length ||
			    bi->info.sp.host_sp_queues_initialized >=
			    css->iomem_length)
				goto bad_fw;
		}
		if (bi->type != IMGU_FW_ISP_FIRMWARE)
			continue;

		if (bi->info.isp.sp.pipeline.mode >= IPU3_CSS_PIPE_ID_NUM)
			goto bad_fw;

		if (bi->info.isp.sp.iterator.num_stripes >
		    IPU3_UAPI_MAX_STRIPES)
			goto bad_fw;

		if (bi->info.isp.num_vf_formats > IMGU_ABI_FRAME_FORMAT_NUM ||
		    bi->info.isp.num_output_formats > IMGU_ABI_FRAME_FORMAT_NUM)
			goto bad_fw;

		for (j = 0; j < bi->info.isp.num_output_formats; j++)
			if (bi->info.isp.output_formats[j] >=
			    IMGU_ABI_FRAME_FORMAT_NUM)
				goto bad_fw;
		for (j = 0; j < bi->info.isp.num_vf_formats; j++)
			if (bi->info.isp.vf_formats[j] >=
			    IMGU_ABI_FRAME_FORMAT_NUM)
				goto bad_fw;

		if (bi->info.isp.sp.block.block_width <= 0 ||
		    bi->info.isp.sp.block.block_width > BLOCK_MAX ||
		    bi->info.isp.sp.block.output_block_height <= 0 ||
		    bi->info.isp.sp.block.output_block_height > BLOCK_MAX)
			goto bad_fw;

		if (bi->blob.memory_offsets.offsets[IMGU_ABI_PARAM_CLASS_PARAM]
		    + sizeof(struct imgu_fw_param_memory_offsets) >
		    css->fw->size ||
		    bi->blob.memory_offsets.offsets[IMGU_ABI_PARAM_CLASS_CONFIG]
		    + sizeof(struct imgu_fw_config_memory_offsets) >
		    css->fw->size ||
		    bi->blob.memory_offsets.offsets[IMGU_ABI_PARAM_CLASS_STATE]
		    + sizeof(struct imgu_fw_state_memory_offsets) >
		    css->fw->size)
			goto bad_fw;

		imgu_css_fw_show_binary(dev, bi, name);
	}

	if (css->fw_bl == -1 || css->fw_sp[0] == -1 || css->fw_sp[1] == -1)
		goto bad_fw;

	/* Allocate and map fw binaries into IMGU */

	css->binary = kcalloc(binary_nr, sizeof(*css->binary), GFP_KERNEL);
	if (!css->binary) {
		r = -ENOMEM;
		goto error_out;
	}

	for (i = 0; i < css->fwp->file_header.binary_nr; i++) {
		struct imgu_fw_info *bi = &css->fwp->binary_header[i];
		void *blob = (void *)css->fwp + bi->blob.offset;
		size_t size = bi->blob.size;

		if (!imgu_dmamap_alloc(imgu, &css->binary[i], size)) {
			r = -ENOMEM;
			goto error_out;
		}
		memcpy(css->binary[i].vaddr, blob, size);
	}

	return 0;

bad_fw:
	dev_err(dev, "invalid firmware binary, size %u\n", (int)css->fw->size);
	r = -ENODEV;

error_out:
	imgu_css_fw_cleanup(css);
	return r;
}