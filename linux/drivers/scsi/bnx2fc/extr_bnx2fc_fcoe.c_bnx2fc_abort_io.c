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

__attribute__((used)) static void bnx2fc_abort_io(struct fc_lport *lport)
{
	/*
	 * This function is no-op for bnx2fc, but we do
	 * not want to leave it as NULL either, as libfc
	 * can call the default function which is
	 * fc_fcp_abort_io.
	 */
}