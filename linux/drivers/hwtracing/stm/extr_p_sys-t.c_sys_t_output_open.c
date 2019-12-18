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
struct sys_t_policy_node {int dummy; } ;
struct sys_t_output {int /*<<< orphan*/  node; } ;
struct stm_output {struct sys_t_output* pdrv_private; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sys_t_output* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sys_t_policy_node*,int) ; 

__attribute__((used)) static int sys_t_output_open(void *priv, struct stm_output *output)
{
	struct sys_t_policy_node *pn = priv;
	struct sys_t_output *opriv;

	opriv = kzalloc(sizeof(*opriv), GFP_ATOMIC);
	if (!opriv)
		return -ENOMEM;

	memcpy(&opriv->node, pn, sizeof(opriv->node));
	output->pdrv_private = opriv;

	return 0;
}