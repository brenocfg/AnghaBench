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
struct fc_lport {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void qedf_fcp_cleanup(struct fc_lport *lport)
{
	/*
	 * NO-OP but need to fill in template to prevent a NULL
	 * function pointer dereference during link down. I/Os
	 * will be flushed when port is uploaded.
	 */
}