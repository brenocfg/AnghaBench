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
struct its_node {int dummy; } ;
struct its_collection {int dummy; } ;
struct TYPE_2__ {struct its_collection* col; } ;
struct its_cmd_desc {TYPE_1__ its_invall_cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  its_build_invall_cmd ; 
 int /*<<< orphan*/  its_send_single_command (struct its_node*,int /*<<< orphan*/ ,struct its_cmd_desc*) ; 

__attribute__((used)) static void its_send_invall(struct its_node *its, struct its_collection *col)
{
	struct its_cmd_desc desc;

	desc.its_invall_cmd.col = col;

	its_send_single_command(its, its_build_invall_cmd, &desc);
}