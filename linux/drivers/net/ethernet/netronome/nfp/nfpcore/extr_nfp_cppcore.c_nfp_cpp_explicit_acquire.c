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
struct nfp_cpp_explicit {struct nfp_cpp* cpp; } ;
struct nfp_cpp {TYPE_1__* op; } ;
struct TYPE_2__ {scalar_t__ explicit_priv_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int NFP_EXPL_OP (int /*<<< orphan*/ ,struct nfp_cpp_explicit*) ; 
 int /*<<< orphan*/  explicit_acquire ; 
 int /*<<< orphan*/  kfree (struct nfp_cpp_explicit*) ; 
 struct nfp_cpp_explicit* kzalloc (scalar_t__,int /*<<< orphan*/ ) ; 

struct nfp_cpp_explicit *nfp_cpp_explicit_acquire(struct nfp_cpp *cpp)
{
	struct nfp_cpp_explicit *expl;
	int err;

	expl = kzalloc(sizeof(*expl) + cpp->op->explicit_priv_size, GFP_KERNEL);
	if (!expl)
		return NULL;

	expl->cpp = cpp;
	err = NFP_EXPL_OP(explicit_acquire, expl);
	if (err < 0) {
		kfree(expl);
		return NULL;
	}

	return expl;
}