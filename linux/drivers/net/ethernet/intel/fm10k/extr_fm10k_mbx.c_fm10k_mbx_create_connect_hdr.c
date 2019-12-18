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
struct TYPE_2__ {scalar_t__ size; } ;
struct fm10k_mbx_info {int mbx_hdr; TYPE_1__ rx; scalar_t__ head; int /*<<< orphan*/  mbx_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONNECT_SIZE ; 
 int /*<<< orphan*/  FM10K_MBX_REQ ; 
 scalar_t__ FM10K_MSG_CONNECT ; 
 int FM10K_MSG_HDR_FIELD_SET (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEAD ; 
 int /*<<< orphan*/  TYPE ; 

__attribute__((used)) static void fm10k_mbx_create_connect_hdr(struct fm10k_mbx_info *mbx)
{
	mbx->mbx_lock |= FM10K_MBX_REQ;

	mbx->mbx_hdr = FM10K_MSG_HDR_FIELD_SET(FM10K_MSG_CONNECT, TYPE) |
		       FM10K_MSG_HDR_FIELD_SET(mbx->head, HEAD) |
		       FM10K_MSG_HDR_FIELD_SET(mbx->rx.size - 1, CONNECT_SIZE);
}