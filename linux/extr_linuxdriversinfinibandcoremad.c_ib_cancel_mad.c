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
struct ib_mad_send_buf {int dummy; } ;
struct ib_mad_agent {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_modify_mad (struct ib_mad_agent*,struct ib_mad_send_buf*,int /*<<< orphan*/ ) ; 

void ib_cancel_mad(struct ib_mad_agent *mad_agent,
		   struct ib_mad_send_buf *send_buf)
{
	ib_modify_mad(mad_agent, send_buf, 0);
}