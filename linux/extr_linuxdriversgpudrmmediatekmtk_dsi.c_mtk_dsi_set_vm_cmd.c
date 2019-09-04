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
struct mtk_dsi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSI_VM_CMD_CON ; 
 int /*<<< orphan*/  TS_VFP_EN ; 
 int /*<<< orphan*/  VM_CMD_EN ; 
 int /*<<< orphan*/  mtk_dsi_mask (struct mtk_dsi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mtk_dsi_set_vm_cmd(struct mtk_dsi *dsi)
{
	mtk_dsi_mask(dsi, DSI_VM_CMD_CON, VM_CMD_EN, VM_CMD_EN);
	mtk_dsi_mask(dsi, DSI_VM_CMD_CON, TS_VFP_EN, TS_VFP_EN);
}