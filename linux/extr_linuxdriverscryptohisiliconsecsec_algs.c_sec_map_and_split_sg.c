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
struct scatterlist {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dma_map_sg (struct device*,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,struct scatterlist*,int,int /*<<< orphan*/ ) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int sg_split (struct scatterlist*,int,int /*<<< orphan*/ ,int,size_t*,struct scatterlist**,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sec_map_and_split_sg(struct scatterlist *sgl, size_t *split_sizes,
				int steps, struct scatterlist ***splits,
				int **splits_nents,
				int sgl_len_in,
				struct device *dev)
{
	int ret, count;

	count = dma_map_sg(dev, sgl, sgl_len_in, DMA_BIDIRECTIONAL);
	if (!count)
		return -EINVAL;

	*splits = kcalloc(steps, sizeof(struct scatterlist *), GFP_KERNEL);
	if (!*splits) {
		ret = -ENOMEM;
		goto err_unmap_sg;
	}
	*splits_nents = kcalloc(steps, sizeof(int), GFP_KERNEL);
	if (!*splits_nents) {
		ret = -ENOMEM;
		goto err_free_splits;
	}

	/* output the scatter list before and after this */
	ret = sg_split(sgl, count, 0, steps, split_sizes,
		       *splits, *splits_nents, GFP_KERNEL);
	if (ret) {
		ret = -ENOMEM;
		goto err_free_splits_nents;
	}

	return 0;

err_free_splits_nents:
	kfree(*splits_nents);
err_free_splits:
	kfree(*splits);
err_unmap_sg:
	dma_unmap_sg(dev, sgl, sgl_len_in, DMA_BIDIRECTIONAL);

	return ret;
}