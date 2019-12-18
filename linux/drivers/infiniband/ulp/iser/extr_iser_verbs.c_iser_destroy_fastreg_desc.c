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
struct iser_reg_resources {int /*<<< orphan*/ * sig_mr; int /*<<< orphan*/ * mr; } ;
struct iser_fr_desc {struct iser_reg_resources rsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ib_dereg_mr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct iser_fr_desc*) ; 

__attribute__((used)) static void iser_destroy_fastreg_desc(struct iser_fr_desc *desc)
{
	struct iser_reg_resources *res = &desc->rsc;

	ib_dereg_mr(res->mr);
	if (res->sig_mr) {
		ib_dereg_mr(res->sig_mr);
		res->sig_mr = NULL;
	}
	kfree(desc);
}