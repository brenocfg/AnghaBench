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
struct artpec6_crypto_walk {int /*<<< orphan*/  offset; int /*<<< orphan*/  sg; } ;
struct artpec6_crypto_req_common {TYPE_1__* dma; int /*<<< orphan*/  gfp_flags; } ;
struct artpec6_crypto_bounce_buffer {size_t length; int /*<<< orphan*/  list; int /*<<< orphan*/  buf; int /*<<< orphan*/  offset; int /*<<< orphan*/  sg; } ;
struct TYPE_2__ {int /*<<< orphan*/  bounce_buffers; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct artpec6_crypto_bounce_buffer* artpec6_crypto_alloc_bounce (int /*<<< orphan*/ ) ; 
 int artpec6_crypto_setup_in_descr (struct artpec6_crypto_req_common*,int /*<<< orphan*/ ,size_t,int) ; 
 int /*<<< orphan*/  kfree (struct artpec6_crypto_bounce_buffer*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int setup_bounce_buffer_in(struct artpec6_crypto_req_common *common,
				  struct artpec6_crypto_walk *walk, size_t size)
{
	struct artpec6_crypto_bounce_buffer *bbuf;
	int ret;

	bbuf = artpec6_crypto_alloc_bounce(common->gfp_flags);
	if (!bbuf)
		return -ENOMEM;

	bbuf->length = size;
	bbuf->sg = walk->sg;
	bbuf->offset = walk->offset;

	ret =  artpec6_crypto_setup_in_descr(common, bbuf->buf, size, false);
	if (ret) {
		kfree(bbuf);
		return ret;
	}

	pr_debug("BOUNCE %zu offset %zu\n", size, walk->offset);
	list_add_tail(&bbuf->list, &common->dma->bounce_buffers);
	return 0;
}