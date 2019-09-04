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
typedef  int /*<<< orphan*/  u64 ;
struct nfp_cpp_explicit {int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 int NFP_EXPL_OP (int /*<<< orphan*/ ,struct nfp_cpp_explicit*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  explicit_do ; 

int nfp_cpp_explicit_do(struct nfp_cpp_explicit *expl, u64 address)
{
	return NFP_EXPL_OP(explicit_do, expl, &expl->cmd, address);
}