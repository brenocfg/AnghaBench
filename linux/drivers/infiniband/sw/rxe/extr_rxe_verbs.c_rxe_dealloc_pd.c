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
struct rxe_pd {int dummy; } ;
struct ib_udata {int dummy; } ;
struct ib_pd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rxe_drop_ref (struct rxe_pd*) ; 
 struct rxe_pd* to_rpd (struct ib_pd*) ; 

__attribute__((used)) static void rxe_dealloc_pd(struct ib_pd *ibpd, struct ib_udata *udata)
{
	struct rxe_pd *pd = to_rpd(ibpd);

	rxe_drop_ref(pd);
}