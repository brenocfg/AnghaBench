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
struct its_vpe {size_t col_idx; } ;
struct its_node {int /*<<< orphan*/ * collections; } ;
struct TYPE_2__ {int valid; int /*<<< orphan*/ * col; struct its_vpe* vpe; } ;
struct its_cmd_desc {TYPE_1__ its_vmapp_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  its_build_vmapp_cmd ; 
 int /*<<< orphan*/  its_send_single_vcommand (struct its_node*,int /*<<< orphan*/ ,struct its_cmd_desc*) ; 

__attribute__((used)) static void its_send_vmapp(struct its_node *its,
			   struct its_vpe *vpe, bool valid)
{
	struct its_cmd_desc desc;

	desc.its_vmapp_cmd.vpe = vpe;
	desc.its_vmapp_cmd.valid = valid;
	desc.its_vmapp_cmd.col = &its->collections[vpe->col_idx];

	its_send_single_vcommand(its, its_build_vmapp_cmd, &desc);
}