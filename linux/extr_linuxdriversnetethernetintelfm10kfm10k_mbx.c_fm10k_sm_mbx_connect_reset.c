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
struct fm10k_mbx_info {int tail; int head; int /*<<< orphan*/  state; scalar_t__ remote; int /*<<< orphan*/  local; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM10K_SM_MBX_VERSION ; 
 int /*<<< orphan*/  FM10K_STATE_CONNECT ; 
 int /*<<< orphan*/  fm10k_mbx_reset_work (struct fm10k_mbx_info*) ; 

__attribute__((used)) static void fm10k_sm_mbx_connect_reset(struct fm10k_mbx_info *mbx)
{
	/* flush any uncompleted work */
	fm10k_mbx_reset_work(mbx);

	/* set local version to max and remote version to 0 */
	mbx->local = FM10K_SM_MBX_VERSION;
	mbx->remote = 0;

	/* initialize tail and head */
	mbx->tail = 1;
	mbx->head = 1;

	/* reset state back to connect */
	mbx->state = FM10K_STATE_CONNECT;
}