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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;
struct mlx5_cmd_msg {TYPE_1__ first; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_in ; 
 int /*<<< orphan*/  opcode ; 

__attribute__((used)) static u16 msg_to_opcode(struct mlx5_cmd_msg *in)
{
	return MLX5_GET(mbox_in, in->first.data, opcode);
}