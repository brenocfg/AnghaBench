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
struct bnx2x_fastpath {scalar_t__ rx_buf_size; scalar_t__ rx_frag_size; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 scalar_t__ NET_SKB_PAD ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfpflags_allow_blocking (int /*<<< orphan*/ ) ; 
 void* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 void* napi_alloc_frag (scalar_t__) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *bnx2x_frag_alloc(const struct bnx2x_fastpath *fp, gfp_t gfp_mask)
{
	if (fp->rx_frag_size) {
		/* GFP_KERNEL allocations are used only during initialization */
		if (unlikely(gfpflags_allow_blocking(gfp_mask)))
			return (void *)__get_free_page(gfp_mask);

		return napi_alloc_frag(fp->rx_frag_size);
	}

	return kmalloc(fp->rx_buf_size + NET_SKB_PAD, gfp_mask);
}