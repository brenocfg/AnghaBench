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
typedef  int /*<<< orphan*/  u8 ;
struct ucma_context {int /*<<< orphan*/  cm_id; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
#define  RDMA_OPTION_ID_ACK_TIMEOUT 131 
#define  RDMA_OPTION_ID_AFONLY 130 
#define  RDMA_OPTION_ID_REUSEADDR 129 
#define  RDMA_OPTION_ID_TOS 128 
 int rdma_set_ack_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdma_set_afonly (int /*<<< orphan*/ ,int) ; 
 int rdma_set_reuseaddr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_set_service_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ucma_set_option_id(struct ucma_context *ctx, int optname,
			      void *optval, size_t optlen)
{
	int ret = 0;

	switch (optname) {
	case RDMA_OPTION_ID_TOS:
		if (optlen != sizeof(u8)) {
			ret = -EINVAL;
			break;
		}
		rdma_set_service_type(ctx->cm_id, *((u8 *) optval));
		break;
	case RDMA_OPTION_ID_REUSEADDR:
		if (optlen != sizeof(int)) {
			ret = -EINVAL;
			break;
		}
		ret = rdma_set_reuseaddr(ctx->cm_id, *((int *) optval) ? 1 : 0);
		break;
	case RDMA_OPTION_ID_AFONLY:
		if (optlen != sizeof(int)) {
			ret = -EINVAL;
			break;
		}
		ret = rdma_set_afonly(ctx->cm_id, *((int *) optval) ? 1 : 0);
		break;
	case RDMA_OPTION_ID_ACK_TIMEOUT:
		if (optlen != sizeof(u8)) {
			ret = -EINVAL;
			break;
		}
		ret = rdma_set_ack_timeout(ctx->cm_id, *((u8 *)optval));
		break;
	default:
		ret = -ENOSYS;
	}

	return ret;
}