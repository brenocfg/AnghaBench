#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct mvumi_res {unsigned int bus_addr; void* virt_addr; } ;
struct mvumi_ob_data {int /*<<< orphan*/  list; } ;
struct TYPE_4__ {int size; void* stack; } ;
struct mvumi_hba {int fw_flag; unsigned int ib_max_size; unsigned int max_io; int hba_capability; int ob_max_size; unsigned int ib_list_phys; unsigned int ib_frame_phys; unsigned int ib_shadow_phys; unsigned int ob_shadow_phys; unsigned int ob_list_phys; unsigned int max_target_id; void* target_map; void* tag_cmd; TYPE_2__ tag_pool; TYPE_1__* pdev; int /*<<< orphan*/  ob_data_list; void* ob_list; void* ob_shadow; void* ib_shadow; void* ib_frame; void* ib_list; } ;
struct mvumi_dyn_list_entry {int dummy; } ;
struct mvumi_cmd {int dummy; } ;
typedef  unsigned int dma_addr_t ;
struct TYPE_3__ {scalar_t__ device; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HS_CAPABILITY_SUPPORT_DYN_SRC ; 
 int MVUMI_FW_ALLOC ; 
 scalar_t__ PCI_DEVICE_ID_MARVELL_MV9580 ; 
 int /*<<< orphan*/  RESOURCE_CACHED_MEMORY ; 
 int /*<<< orphan*/  RESOURCE_UNCACHED_MEMORY ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct mvumi_res* mvumi_alloc_mem_resource (struct mvumi_hba*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mvumi_release_mem_resource (struct mvumi_hba*) ; 
 int round_up (unsigned int,int) ; 
 int /*<<< orphan*/  tag_init (TYPE_2__*,int) ; 

__attribute__((used)) static int mvumi_init_data(struct mvumi_hba *mhba)
{
	struct mvumi_ob_data *ob_pool;
	struct mvumi_res *res_mgnt;
	unsigned int tmp_size, offset, i;
	void *virmem, *v;
	dma_addr_t p;

	if (mhba->fw_flag & MVUMI_FW_ALLOC)
		return 0;

	tmp_size = mhba->ib_max_size * mhba->max_io;
	if (mhba->hba_capability & HS_CAPABILITY_SUPPORT_DYN_SRC)
		tmp_size += sizeof(struct mvumi_dyn_list_entry) * mhba->max_io;

	tmp_size += 128 + mhba->ob_max_size * mhba->max_io;
	tmp_size += 8 + sizeof(u32)*2 + 16;

	res_mgnt = mvumi_alloc_mem_resource(mhba,
					RESOURCE_UNCACHED_MEMORY, tmp_size);
	if (!res_mgnt) {
		dev_err(&mhba->pdev->dev,
			"failed to allocate memory for inbound list\n");
		goto fail_alloc_dma_buf;
	}

	p = res_mgnt->bus_addr;
	v = res_mgnt->virt_addr;
	/* ib_list */
	offset = round_up(p, 128) - p;
	p += offset;
	v += offset;
	mhba->ib_list = v;
	mhba->ib_list_phys = p;
	if (mhba->hba_capability & HS_CAPABILITY_SUPPORT_DYN_SRC) {
		v += sizeof(struct mvumi_dyn_list_entry) * mhba->max_io;
		p += sizeof(struct mvumi_dyn_list_entry) * mhba->max_io;
		mhba->ib_frame = v;
		mhba->ib_frame_phys = p;
	}
	v += mhba->ib_max_size * mhba->max_io;
	p += mhba->ib_max_size * mhba->max_io;

	/* ib shadow */
	offset = round_up(p, 8) - p;
	p += offset;
	v += offset;
	mhba->ib_shadow = v;
	mhba->ib_shadow_phys = p;
	p += sizeof(u32)*2;
	v += sizeof(u32)*2;
	/* ob shadow */
	if (mhba->pdev->device == PCI_DEVICE_ID_MARVELL_MV9580) {
		offset = round_up(p, 8) - p;
		p += offset;
		v += offset;
		mhba->ob_shadow = v;
		mhba->ob_shadow_phys = p;
		p += 8;
		v += 8;
	} else {
		offset = round_up(p, 4) - p;
		p += offset;
		v += offset;
		mhba->ob_shadow = v;
		mhba->ob_shadow_phys = p;
		p += 4;
		v += 4;
	}

	/* ob list */
	offset = round_up(p, 128) - p;
	p += offset;
	v += offset;

	mhba->ob_list = v;
	mhba->ob_list_phys = p;

	/* ob data pool */
	tmp_size = mhba->max_io * (mhba->ob_max_size + sizeof(*ob_pool));
	tmp_size = round_up(tmp_size, 8);

	res_mgnt = mvumi_alloc_mem_resource(mhba,
				RESOURCE_CACHED_MEMORY, tmp_size);
	if (!res_mgnt) {
		dev_err(&mhba->pdev->dev,
			"failed to allocate memory for outbound data buffer\n");
		goto fail_alloc_dma_buf;
	}
	virmem = res_mgnt->virt_addr;

	for (i = mhba->max_io; i != 0; i--) {
		ob_pool = (struct mvumi_ob_data *) virmem;
		list_add_tail(&ob_pool->list, &mhba->ob_data_list);
		virmem += mhba->ob_max_size + sizeof(*ob_pool);
	}

	tmp_size = sizeof(unsigned short) * mhba->max_io +
				sizeof(struct mvumi_cmd *) * mhba->max_io;
	tmp_size += round_up(mhba->max_target_id, sizeof(unsigned char) * 8) /
						(sizeof(unsigned char) * 8);

	res_mgnt = mvumi_alloc_mem_resource(mhba,
				RESOURCE_CACHED_MEMORY, tmp_size);
	if (!res_mgnt) {
		dev_err(&mhba->pdev->dev,
			"failed to allocate memory for tag and target map\n");
		goto fail_alloc_dma_buf;
	}

	virmem = res_mgnt->virt_addr;
	mhba->tag_pool.stack = virmem;
	mhba->tag_pool.size = mhba->max_io;
	tag_init(&mhba->tag_pool, mhba->max_io);
	virmem += sizeof(unsigned short) * mhba->max_io;

	mhba->tag_cmd = virmem;
	virmem += sizeof(struct mvumi_cmd *) * mhba->max_io;

	mhba->target_map = virmem;

	mhba->fw_flag |= MVUMI_FW_ALLOC;
	return 0;

fail_alloc_dma_buf:
	mvumi_release_mem_resource(mhba);
	return -1;
}