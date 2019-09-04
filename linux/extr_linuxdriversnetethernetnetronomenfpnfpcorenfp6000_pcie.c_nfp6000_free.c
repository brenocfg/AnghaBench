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
struct nfp_cpp {int dummy; } ;
struct nfp6000_pcie {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_bars (struct nfp6000_pcie*) ; 
 int /*<<< orphan*/  kfree (struct nfp6000_pcie*) ; 
 struct nfp6000_pcie* nfp_cpp_priv (struct nfp_cpp*) ; 

__attribute__((used)) static void nfp6000_free(struct nfp_cpp *cpp)
{
	struct nfp6000_pcie *nfp = nfp_cpp_priv(cpp);

	disable_bars(nfp);
	kfree(nfp);
}