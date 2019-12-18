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
struct ib_mad_send_wr_private {int /*<<< orphan*/  timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  wait_for_response (struct ib_mad_send_wr_private*) ; 

void ib_reset_mad_timeout(struct ib_mad_send_wr_private *mad_send_wr,
			  unsigned long timeout_ms)
{
	mad_send_wr->timeout = msecs_to_jiffies(timeout_ms);
	wait_for_response(mad_send_wr);
}