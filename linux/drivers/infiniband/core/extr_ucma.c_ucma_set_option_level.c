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
#define  RDMA_OPTION_IB 129 
#define  RDMA_OPTION_ID 128 
 int ucma_set_option_ib (struct ucma_context*,int,void*,size_t) ; 
 int ucma_set_option_id (struct ucma_context*,int,void*,size_t) ; 

__attribute__((used)) static int ucma_set_option_level(struct ucma_context *ctx, int level,
				 int optname, void *optval, size_t optlen)
{
	int ret;

	switch (level) {
	case RDMA_OPTION_ID:
		ret = ucma_set_option_id(ctx, optname, optval, optlen);
		break;
	case RDMA_OPTION_IB:
		ret = ucma_set_option_ib(ctx, optname, optval, optlen);
		break;
	default:
		ret = -ENOSYS;
	}

	return ret;
}