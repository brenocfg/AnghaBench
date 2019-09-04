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
struct scatterlist {unsigned int offset; unsigned int length; } ;
struct page {int dummy; } ;
struct TYPE_2__ {int flags; struct scatterlist* cache; } ;
struct hifn_request_context {TYPE_1__ walk; } ;
struct hifn_device {int dummy; } ;
struct hifn_context {int dummy; } ;

/* Variables and functions */
 int ASYNC_FLAGS_MISALIGNED ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  hifn_setup_cmd_desc (struct hifn_device*,struct hifn_context*,struct hifn_request_context*,void*,unsigned int) ; 
 int /*<<< orphan*/  hifn_setup_dst_desc (struct hifn_device*,struct page*,unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  hifn_setup_res_desc (struct hifn_device*) ; 
 int /*<<< orphan*/  hifn_setup_src_desc (struct hifn_device*,struct page*,unsigned int,unsigned int,int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 struct page* sg_page (struct scatterlist*) ; 

__attribute__((used)) static int hifn_setup_dma(struct hifn_device *dev,
		struct hifn_context *ctx, struct hifn_request_context *rctx,
		struct scatterlist *src, struct scatterlist *dst,
		unsigned int nbytes, void *priv)
{
	struct scatterlist *t;
	struct page *spage, *dpage;
	unsigned int soff, doff;
	unsigned int n, len;

	n = nbytes;
	while (n) {
		spage = sg_page(src);
		soff = src->offset;
		len = min(src->length, n);

		hifn_setup_src_desc(dev, spage, soff, len, n - len == 0);

		src++;
		n -= len;
	}

	t = &rctx->walk.cache[0];
	n = nbytes;
	while (n) {
		if (t->length && rctx->walk.flags & ASYNC_FLAGS_MISALIGNED) {
			BUG_ON(!sg_page(t));
			dpage = sg_page(t);
			doff = 0;
			len = t->length;
		} else {
			BUG_ON(!sg_page(dst));
			dpage = sg_page(dst);
			doff = dst->offset;
			len = dst->length;
		}
		len = min(len, n);

		hifn_setup_dst_desc(dev, dpage, doff, len, n - len == 0);

		dst++;
		t++;
		n -= len;
	}

	hifn_setup_cmd_desc(dev, ctx, rctx, priv, nbytes);
	hifn_setup_res_desc(dev);
	return 0;
}