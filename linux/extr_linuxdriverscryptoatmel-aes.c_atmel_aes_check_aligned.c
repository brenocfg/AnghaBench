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
typedef  int /*<<< orphan*/  u32 ;
struct scatterlist {size_t offset; size_t length; } ;
struct atmel_aes_dma {int nents; size_t remainder; } ;
struct atmel_aes_dev {TYPE_1__* ctx; } ;
struct TYPE_2__ {int block_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ALIGNED (size_t,int) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static bool atmel_aes_check_aligned(struct atmel_aes_dev *dd,
				    struct scatterlist *sg,
				    size_t len,
				    struct atmel_aes_dma *dma)
{
	int nents;

	if (!IS_ALIGNED(len, dd->ctx->block_size))
		return false;

	for (nents = 0; sg; sg = sg_next(sg), ++nents) {
		if (!IS_ALIGNED(sg->offset, sizeof(u32)))
			return false;

		if (len <= sg->length) {
			if (!IS_ALIGNED(len, dd->ctx->block_size))
				return false;

			dma->nents = nents+1;
			dma->remainder = sg->length - len;
			sg->length = len;
			return true;
		}

		if (!IS_ALIGNED(sg->length, dd->ctx->block_size))
			return false;

		len -= sg->length;
	}

	return false;
}