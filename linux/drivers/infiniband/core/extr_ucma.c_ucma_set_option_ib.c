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
struct ucma_context {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 
#define  RDMA_OPTION_IB_PATH 128 
 int ucma_set_ib_path (struct ucma_context*,void*,size_t) ; 

__attribute__((used)) static int ucma_set_option_ib(struct ucma_context *ctx, int optname,
			      void *optval, size_t optlen)
{
	int ret;

	switch (optname) {
	case RDMA_OPTION_IB_PATH:
		ret = ucma_set_ib_path(ctx, optval, optlen);
		break;
	default:
		ret = -ENOSYS;
	}

	return ret;
}