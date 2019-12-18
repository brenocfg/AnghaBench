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
typedef  scalar_t__ u8 ;
struct mlx5_cmd {scalar_t__ token; int /*<<< orphan*/  token_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u8 alloc_token(struct mlx5_cmd *cmd)
{
	u8 token;

	spin_lock(&cmd->token_lock);
	cmd->token++;
	if (cmd->token == 0)
		cmd->token++;
	token = cmd->token;
	spin_unlock(&cmd->token_lock);

	return token;
}