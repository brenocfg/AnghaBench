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
struct nfp_cpp_area {int dummy; } ;
struct nfp6000_area_priv {int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 struct nfp6000_area_priv* nfp_cpp_area_priv (struct nfp_cpp_area*) ; 

__attribute__((used)) static int priv_area_put(struct nfp_cpp_area *area)
{
	struct nfp6000_area_priv *priv = nfp_cpp_area_priv(area);

	if (WARN_ON(!atomic_read(&priv->refcnt)))
		return 0;

	return atomic_dec_and_test(&priv->refcnt);
}