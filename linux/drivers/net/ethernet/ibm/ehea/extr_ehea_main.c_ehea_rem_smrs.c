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
struct ehea_port_res {int /*<<< orphan*/  recv_mr; int /*<<< orphan*/  send_mr; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ ehea_rem_mr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ehea_rem_smrs(struct ehea_port_res *pr)
{
	if ((ehea_rem_mr(&pr->send_mr)) ||
	    (ehea_rem_mr(&pr->recv_mr)))
		return -EIO;
	else
		return 0;
}