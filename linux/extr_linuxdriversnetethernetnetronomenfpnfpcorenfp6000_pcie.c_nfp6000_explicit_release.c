#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nfp_cpp_explicit {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  mutex; TYPE_1__* group; } ;
struct nfp6000_pcie {TYPE_2__ expl; } ;
struct TYPE_6__ {size_t group; size_t area; } ;
struct nfp6000_explicit_priv {TYPE_3__ bar; struct nfp6000_pcie* nfp; } ;
struct TYPE_4__ {int* free; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct nfp6000_explicit_priv* nfp_cpp_explicit_priv (struct nfp_cpp_explicit*) ; 

__attribute__((used)) static void nfp6000_explicit_release(struct nfp_cpp_explicit *expl)
{
	struct nfp6000_explicit_priv *priv = nfp_cpp_explicit_priv(expl);
	struct nfp6000_pcie *nfp = priv->nfp;

	mutex_lock(&nfp->expl.mutex);
	nfp->expl.group[priv->bar.group].free[priv->bar.area] = true;
	mutex_unlock(&nfp->expl.mutex);
}