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
struct nfp_cpp_explicit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFP_EXPL_OP_NR (int /*<<< orphan*/ ,struct nfp_cpp_explicit*) ; 
 int /*<<< orphan*/  explicit_release ; 
 int /*<<< orphan*/  kfree (struct nfp_cpp_explicit*) ; 

void nfp_cpp_explicit_release(struct nfp_cpp_explicit *expl)
{
	NFP_EXPL_OP_NR(explicit_release, expl);
	kfree(expl);
}