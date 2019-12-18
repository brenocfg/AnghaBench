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
struct fcloop_tport {int /*<<< orphan*/  targetport; } ;
struct fcloop_nport {int dummy; } ;

/* Variables and functions */
 int EALREADY ; 
 int nvmet_fc_unregister_targetport (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
__targetport_unreg(struct fcloop_nport *nport, struct fcloop_tport *tport)
{
	if (!tport)
		return -EALREADY;

	return nvmet_fc_unregister_targetport(tport->targetport);
}