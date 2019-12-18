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
struct stp_policy_node {void* priv; } ;

/* Variables and functions */

void *stp_policy_node_priv(struct stp_policy_node *pn)
{
	if (!pn)
		return NULL;

	return pn->priv;
}