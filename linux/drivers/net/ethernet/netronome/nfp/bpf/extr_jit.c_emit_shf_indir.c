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
typedef  int /*<<< orphan*/  swreg ;
struct nfp_prog {int /*<<< orphan*/  error; } ;
typedef  enum shf_sc { ____Placeholder_shf_sc } shf_sc ;
typedef  enum shf_op { ____Placeholder_shf_op } shf_op ;

/* Variables and functions */
 int /*<<< orphan*/  EFAULT ; 
 int SHF_SC_R_ROT ; 
 int /*<<< orphan*/  emit_shf (struct nfp_prog*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void
emit_shf_indir(struct nfp_prog *nfp_prog, swreg dst,
	       swreg lreg, enum shf_op op, swreg rreg, enum shf_sc sc)
{
	if (sc == SHF_SC_R_ROT) {
		pr_err("indirect shift is not allowed on rotation\n");
		nfp_prog->error = -EFAULT;
		return;
	}

	emit_shf(nfp_prog, dst, lreg, op, rreg, sc, 0);
}