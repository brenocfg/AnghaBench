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
struct bnx2x_queue_update_params {int /*<<< orphan*/  update_flags; } ;
struct TYPE_2__ {struct bnx2x_queue_update_params update; } ;
struct bnx2x_queue_state_params {TYPE_1__ params; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_Q_UPDATE_ACTIVATE_CHNG ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int bnx2x_q_send_update (struct bnx2x*,struct bnx2x_queue_state_params*) ; 
 int /*<<< orphan*/  memset (struct bnx2x_queue_update_params*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline int bnx2x_q_send_deactivate(struct bnx2x *bp,
					struct bnx2x_queue_state_params *params)
{
	struct bnx2x_queue_update_params *update = &params->params.update;

	memset(update, 0, sizeof(*update));

	__set_bit(BNX2X_Q_UPDATE_ACTIVATE_CHNG, &update->update_flags);

	return bnx2x_q_send_update(bp, params);
}