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
struct tb {int /*<<< orphan*/  nhi; } ;

/* Variables and functions */
 int /*<<< orphan*/  NHI_MAILBOX_DISCONNECT_PCIE_PATHS ; 
 int nhi_mailbox_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int icm_disconnect_pcie_paths(struct tb *tb)
{
	return nhi_mailbox_cmd(tb->nhi, NHI_MAILBOX_DISCONNECT_PCIE_PATHS, 0);
}