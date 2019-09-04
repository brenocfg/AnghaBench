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
struct i40iw_cqp_request {int /*<<< orphan*/  param; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_send_syn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i40iw_send_syn_cqp_callback(struct i40iw_cqp_request *cqp_request, u32 send_ack)
{
	i40iw_send_syn(cqp_request->param, send_ack);
}