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
struct fm10k_mbx_info {scalar_t__ state; void* remote; void* local; } ;

/* Variables and functions */
 void* FM10K_MBX_CRC_SEED ; 
 scalar_t__ FM10K_STATE_CLOSED ; 
 scalar_t__ FM10K_STATE_CONNECT ; 
 scalar_t__ FM10K_STATE_OPEN ; 
 int /*<<< orphan*/  fm10k_mbx_reset_work (struct fm10k_mbx_info*) ; 

__attribute__((used)) static void fm10k_mbx_connect_reset(struct fm10k_mbx_info *mbx)
{
	/* just do a quick resysnc to start of frame */
	fm10k_mbx_reset_work(mbx);

	/* reset CRC seeds */
	mbx->local = FM10K_MBX_CRC_SEED;
	mbx->remote = FM10K_MBX_CRC_SEED;

	/* we cannot exit connect until the size is good */
	if (mbx->state == FM10K_STATE_OPEN)
		mbx->state = FM10K_STATE_CONNECT;
	else
		mbx->state = FM10K_STATE_CLOSED;
}