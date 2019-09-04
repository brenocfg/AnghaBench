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
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;
struct caam_hash_state {int ctx_dma_len; scalar_t__ ctx_dma; int /*<<< orphan*/  caam_ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FROM_DEVICE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  append_seq_out_ptr (int /*<<< orphan*/ *,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 scalar_t__ dma_map_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,scalar_t__) ; 

__attribute__((used)) static inline int map_seq_out_ptr_ctx(u32 *desc, struct device *jrdev,
				      struct caam_hash_state *state,
				      int ctx_len)
{
	state->ctx_dma_len = ctx_len;
	state->ctx_dma = dma_map_single(jrdev, state->caam_ctx,
					ctx_len, DMA_FROM_DEVICE);
	if (dma_mapping_error(jrdev, state->ctx_dma)) {
		dev_err(jrdev, "unable to map ctx\n");
		state->ctx_dma = 0;
		return -ENOMEM;
	}

	append_seq_out_ptr(desc, state->ctx_dma, ctx_len, 0);

	return 0;
}