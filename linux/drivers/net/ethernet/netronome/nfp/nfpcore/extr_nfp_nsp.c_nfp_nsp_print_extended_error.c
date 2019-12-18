#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct nfp_nsp {int /*<<< orphan*/  cpp; } ;
struct TYPE_3__ {scalar_t__ code; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  nfp_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 TYPE_1__* nsp_errors ; 

__attribute__((used)) static void nfp_nsp_print_extended_error(struct nfp_nsp *state, u32 ret_val)
{
	int i;

	if (!ret_val)
		return;

	for (i = 0; i < ARRAY_SIZE(nsp_errors); i++)
		if (ret_val == nsp_errors[i].code)
			nfp_err(state->cpp, "err msg: %s\n", nsp_errors[i].msg);
}