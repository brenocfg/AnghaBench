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
struct TYPE_6__ {TYPE_2__* cra_type; } ;
struct crypto_instance {TYPE_3__ alg; TYPE_1__* tmpl; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* free ) (struct crypto_instance*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* free ) (struct crypto_instance*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct crypto_instance*) ; 
 int /*<<< orphan*/  stub2 (struct crypto_instance*) ; 

__attribute__((used)) static void crypto_free_instance(struct crypto_instance *inst)
{
	if (!inst->alg.cra_type->free) {
		inst->tmpl->free(inst);
		return;
	}

	inst->alg.cra_type->free(inst);
}