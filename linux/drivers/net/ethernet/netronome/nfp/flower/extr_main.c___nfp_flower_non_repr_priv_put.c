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
struct nfp_flower_non_repr_priv {int /*<<< orphan*/  list; scalar_t__ ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct nfp_flower_non_repr_priv*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

void
__nfp_flower_non_repr_priv_put(struct nfp_flower_non_repr_priv *non_repr_priv)
{
	if (--non_repr_priv->ref_count)
		return;

	list_del(&non_repr_priv->list);
	kfree(non_repr_priv);
}