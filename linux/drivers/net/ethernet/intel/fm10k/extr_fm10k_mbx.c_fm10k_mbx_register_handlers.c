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
struct fm10k_msg_data {int dummy; } ;
struct fm10k_mbx_info {struct fm10k_msg_data const* msg_data; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_ERR_PARAM ; 
 scalar_t__ fm10k_mbx_validate_handlers (struct fm10k_msg_data const*) ; 

__attribute__((used)) static s32 fm10k_mbx_register_handlers(struct fm10k_mbx_info *mbx,
				       const struct fm10k_msg_data *msg_data)
{
	/* validate layout of handlers before assigning them */
	if (fm10k_mbx_validate_handlers(msg_data))
		return FM10K_ERR_PARAM;

	/* initialize the message handlers */
	mbx->msg_data = msg_data;

	return 0;
}