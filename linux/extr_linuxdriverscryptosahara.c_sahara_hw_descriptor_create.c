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
struct scatterlist {int /*<<< orphan*/  dma_address; int /*<<< orphan*/  length; } ;
struct sahara_dev {int flags; int nb_in_sg; int nb_out_sg; struct scatterlist* in_sg; int /*<<< orphan*/  device; struct scatterlist* out_sg; scalar_t__* hw_phys_desc; TYPE_1__** hw_desc; scalar_t__ total; scalar_t__* hw_phys_link; TYPE_2__** hw_link; scalar_t__ key_phys_base; scalar_t__ iv_phys_base; int /*<<< orphan*/  key_base; struct sahara_ctx* ctx; } ;
struct sahara_ctx {int flags; scalar_t__ keylen; int /*<<< orphan*/  key; } ;
struct TYPE_4__ {scalar_t__ next; int /*<<< orphan*/  p; int /*<<< orphan*/  len; } ;
struct TYPE_3__ {scalar_t__ next; scalar_t__ len2; scalar_t__ len1; int /*<<< orphan*/  hdr; scalar_t__ p2; scalar_t__ p1; } ;

/* Variables and functions */
 scalar_t__ AES_BLOCK_SIZE ; 
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int FLAGS_CBC ; 
 int FLAGS_NEW_KEY ; 
 scalar_t__ SAHARA_MAX_HW_LINK ; 
 int /*<<< orphan*/  SAHARA_REG_DAR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int dma_map_sg (int /*<<< orphan*/ ,struct scatterlist*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (int /*<<< orphan*/ ,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sahara_aes_data_link_hdr (struct sahara_dev*) ; 
 int /*<<< orphan*/  sahara_aes_key_hdr (struct sahara_dev*) ; 
 int /*<<< orphan*/  sahara_dump_descriptors (struct sahara_dev*) ; 
 int /*<<< orphan*/  sahara_dump_links (struct sahara_dev*) ; 
 int /*<<< orphan*/  sahara_write (struct sahara_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 void* sg_nents_for_len (struct scatterlist*,scalar_t__) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static int sahara_hw_descriptor_create(struct sahara_dev *dev)
{
	struct sahara_ctx *ctx = dev->ctx;
	struct scatterlist *sg;
	int ret;
	int i, j;
	int idx = 0;

	/* Copy new key if necessary */
	if (ctx->flags & FLAGS_NEW_KEY) {
		memcpy(dev->key_base, ctx->key, ctx->keylen);
		ctx->flags &= ~FLAGS_NEW_KEY;

		if (dev->flags & FLAGS_CBC) {
			dev->hw_desc[idx]->len1 = AES_BLOCK_SIZE;
			dev->hw_desc[idx]->p1 = dev->iv_phys_base;
		} else {
			dev->hw_desc[idx]->len1 = 0;
			dev->hw_desc[idx]->p1 = 0;
		}
		dev->hw_desc[idx]->len2 = ctx->keylen;
		dev->hw_desc[idx]->p2 = dev->key_phys_base;
		dev->hw_desc[idx]->next = dev->hw_phys_desc[1];

		dev->hw_desc[idx]->hdr = sahara_aes_key_hdr(dev);

		idx++;
	}

	dev->nb_in_sg = sg_nents_for_len(dev->in_sg, dev->total);
	if (dev->nb_in_sg < 0) {
		dev_err(dev->device, "Invalid numbers of src SG.\n");
		return dev->nb_in_sg;
	}
	dev->nb_out_sg = sg_nents_for_len(dev->out_sg, dev->total);
	if (dev->nb_out_sg < 0) {
		dev_err(dev->device, "Invalid numbers of dst SG.\n");
		return dev->nb_out_sg;
	}
	if ((dev->nb_in_sg + dev->nb_out_sg) > SAHARA_MAX_HW_LINK) {
		dev_err(dev->device, "not enough hw links (%d)\n",
			dev->nb_in_sg + dev->nb_out_sg);
		return -EINVAL;
	}

	ret = dma_map_sg(dev->device, dev->in_sg, dev->nb_in_sg,
			 DMA_TO_DEVICE);
	if (ret != dev->nb_in_sg) {
		dev_err(dev->device, "couldn't map in sg\n");
		goto unmap_in;
	}
	ret = dma_map_sg(dev->device, dev->out_sg, dev->nb_out_sg,
			 DMA_FROM_DEVICE);
	if (ret != dev->nb_out_sg) {
		dev_err(dev->device, "couldn't map out sg\n");
		goto unmap_out;
	}

	/* Create input links */
	dev->hw_desc[idx]->p1 = dev->hw_phys_link[0];
	sg = dev->in_sg;
	for (i = 0; i < dev->nb_in_sg; i++) {
		dev->hw_link[i]->len = sg->length;
		dev->hw_link[i]->p = sg->dma_address;
		if (i == (dev->nb_in_sg - 1)) {
			dev->hw_link[i]->next = 0;
		} else {
			dev->hw_link[i]->next = dev->hw_phys_link[i + 1];
			sg = sg_next(sg);
		}
	}

	/* Create output links */
	dev->hw_desc[idx]->p2 = dev->hw_phys_link[i];
	sg = dev->out_sg;
	for (j = i; j < dev->nb_out_sg + i; j++) {
		dev->hw_link[j]->len = sg->length;
		dev->hw_link[j]->p = sg->dma_address;
		if (j == (dev->nb_out_sg + i - 1)) {
			dev->hw_link[j]->next = 0;
		} else {
			dev->hw_link[j]->next = dev->hw_phys_link[j + 1];
			sg = sg_next(sg);
		}
	}

	/* Fill remaining fields of hw_desc[1] */
	dev->hw_desc[idx]->hdr = sahara_aes_data_link_hdr(dev);
	dev->hw_desc[idx]->len1 = dev->total;
	dev->hw_desc[idx]->len2 = dev->total;
	dev->hw_desc[idx]->next = 0;

	sahara_dump_descriptors(dev);
	sahara_dump_links(dev);

	sahara_write(dev, dev->hw_phys_desc[0], SAHARA_REG_DAR);

	return 0;

unmap_out:
	dma_unmap_sg(dev->device, dev->out_sg, dev->nb_out_sg,
		DMA_FROM_DEVICE);
unmap_in:
	dma_unmap_sg(dev->device, dev->in_sg, dev->nb_in_sg,
		DMA_TO_DEVICE);

	return -EINVAL;
}