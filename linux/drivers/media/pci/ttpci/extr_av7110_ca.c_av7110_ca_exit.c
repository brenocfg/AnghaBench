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
struct av7110 {int /*<<< orphan*/  ci_wbuffer; int /*<<< orphan*/  ci_rbuffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  ci_ll_release (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void av7110_ca_exit(struct av7110* av7110)
{
	ci_ll_release(&av7110->ci_rbuffer, &av7110->ci_wbuffer);
}