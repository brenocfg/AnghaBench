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
struct rxe_ucontext {int dummy; } ;
struct ib_ucontext {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rxe_drop_ref (struct rxe_ucontext*) ; 
 struct rxe_ucontext* to_ruc (struct ib_ucontext*) ; 

__attribute__((used)) static void rxe_dealloc_ucontext(struct ib_ucontext *ibuc)
{
	struct rxe_ucontext *uc = to_ruc(ibuc);

	rxe_drop_ref(uc);
}