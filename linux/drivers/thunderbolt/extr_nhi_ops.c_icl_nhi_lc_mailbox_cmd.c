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
typedef  int u32 ;
struct tb_nhi {int /*<<< orphan*/  pdev; } ;
typedef  enum icl_lc_mailbox_cmd { ____Placeholder_icl_lc_mailbox_cmd } icl_lc_mailbox_cmd ;

/* Variables and functions */
 int /*<<< orphan*/  VS_CAP_19 ; 
 int VS_CAP_19_CMD_MASK ; 
 int VS_CAP_19_CMD_SHIFT ; 
 int VS_CAP_19_VALID ; 
 int /*<<< orphan*/  pci_write_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void icl_nhi_lc_mailbox_cmd(struct tb_nhi *nhi, enum icl_lc_mailbox_cmd cmd)
{
	u32 data;

	data = (cmd << VS_CAP_19_CMD_SHIFT) & VS_CAP_19_CMD_MASK;
	pci_write_config_dword(nhi->pdev, VS_CAP_19, data | VS_CAP_19_VALID);
}