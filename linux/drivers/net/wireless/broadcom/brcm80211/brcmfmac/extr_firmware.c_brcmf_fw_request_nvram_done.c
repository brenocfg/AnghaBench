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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct firmware {size_t size; scalar_t__ data; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; void* data; } ;
struct brcmf_fw_item {int flags; TYPE_2__ nv_data; } ;
struct brcmf_fw {size_t curpos; TYPE_1__* req; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus_nr; int /*<<< orphan*/  domain_nr; struct brcmf_fw_item* items; } ;

/* Variables and functions */
 int BRCMF_FW_REQF_OPTIONAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/ * bcm47xx_nvram_get_contents (size_t*) ; 
 int /*<<< orphan*/  bcm47xx_nvram_release_contents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,void*,...) ; 
 int /*<<< orphan*/ * brcmf_fw_nvram_from_efi (size_t*) ; 
 void* brcmf_fw_nvram_strip (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 

__attribute__((used)) static int brcmf_fw_request_nvram_done(const struct firmware *fw, void *ctx)
{
	struct brcmf_fw *fwctx = ctx;
	struct brcmf_fw_item *cur;
	bool free_bcm47xx_nvram = false;
	bool kfree_nvram = false;
	u32 nvram_length = 0;
	void *nvram = NULL;
	u8 *data = NULL;
	size_t data_len;

	brcmf_dbg(TRACE, "enter: dev=%s\n", dev_name(fwctx->dev));

	cur = &fwctx->req->items[fwctx->curpos];

	if (fw && fw->data) {
		data = (u8 *)fw->data;
		data_len = fw->size;
	} else {
		if ((data = bcm47xx_nvram_get_contents(&data_len)))
			free_bcm47xx_nvram = true;
		else if ((data = brcmf_fw_nvram_from_efi(&data_len)))
			kfree_nvram = true;
		else if (!(cur->flags & BRCMF_FW_REQF_OPTIONAL))
			goto fail;
	}

	if (data)
		nvram = brcmf_fw_nvram_strip(data, data_len, &nvram_length,
					     fwctx->req->domain_nr,
					     fwctx->req->bus_nr);

	if (free_bcm47xx_nvram)
		bcm47xx_nvram_release_contents(data);
	if (kfree_nvram)
		kfree(data);

	release_firmware(fw);
	if (!nvram && !(cur->flags & BRCMF_FW_REQF_OPTIONAL))
		goto fail;

	brcmf_dbg(TRACE, "nvram %p len %d\n", nvram, nvram_length);
	cur->nv_data.data = nvram;
	cur->nv_data.len = nvram_length;
	return 0;

fail:
	return -ENOENT;
}