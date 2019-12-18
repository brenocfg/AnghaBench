#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uuid ;
typedef  int u32 ;
struct tb_nhi {int /*<<< orphan*/  pdev; } ;
struct tb {TYPE_1__* root_switch; struct tb_nhi* nhi; } ;
struct TYPE_2__ {int /*<<< orphan*/  uuid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VS_CAP_10 ; 
 int /*<<< orphan*/  VS_CAP_11 ; 
 int /*<<< orphan*/  kmemdup (int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_read_config_dword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void icm_icl_set_uuid(struct tb *tb)
{
	struct tb_nhi *nhi = tb->nhi;
	u32 uuid[4];

	pci_read_config_dword(nhi->pdev, VS_CAP_10, &uuid[0]);
	pci_read_config_dword(nhi->pdev, VS_CAP_11, &uuid[1]);
	uuid[2] = 0xffffffff;
	uuid[3] = 0xffffffff;

	tb->root_switch->uuid = kmemdup(uuid, sizeof(uuid), GFP_KERNEL);
}