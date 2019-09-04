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
struct hvutil_transport {int /*<<< orphan*/  (* on_reset ) () ;scalar_t__ outmsg_len; int /*<<< orphan*/ * outmsg; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void hvt_reset(struct hvutil_transport *hvt)
{
	kfree(hvt->outmsg);
	hvt->outmsg = NULL;
	hvt->outmsg_len = 0;
	if (hvt->on_reset)
		hvt->on_reset();
}