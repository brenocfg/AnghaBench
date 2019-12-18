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
struct srp_iu {size_t size; int direction; struct srp_iu* buf; int /*<<< orphan*/  dma; } ;
struct srp_host {TYPE_1__* srp_dev; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dma_map_single (int /*<<< orphan*/ ,struct srp_iu*,size_t,int) ; 
 scalar_t__ ib_dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct srp_iu*) ; 
 struct srp_iu* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct srp_iu* kzalloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct srp_iu *srp_alloc_iu(struct srp_host *host, size_t size,
				   gfp_t gfp_mask,
				   enum dma_data_direction direction)
{
	struct srp_iu *iu;

	iu = kmalloc(sizeof *iu, gfp_mask);
	if (!iu)
		goto out;

	iu->buf = kzalloc(size, gfp_mask);
	if (!iu->buf)
		goto out_free_iu;

	iu->dma = ib_dma_map_single(host->srp_dev->dev, iu->buf, size,
				    direction);
	if (ib_dma_mapping_error(host->srp_dev->dev, iu->dma))
		goto out_free_buf;

	iu->size      = size;
	iu->direction = direction;

	return iu;

out_free_buf:
	kfree(iu->buf);
out_free_iu:
	kfree(iu);
out:
	return NULL;
}