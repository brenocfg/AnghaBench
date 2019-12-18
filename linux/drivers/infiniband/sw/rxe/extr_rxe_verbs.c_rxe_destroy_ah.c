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
typedef  int /*<<< orphan*/  u32 ;
struct rxe_ah {int dummy; } ;
struct ib_ah {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rxe_drop_ref (struct rxe_ah*) ; 
 struct rxe_ah* to_rah (struct ib_ah*) ; 

__attribute__((used)) static void rxe_destroy_ah(struct ib_ah *ibah, u32 flags)
{
	struct rxe_ah *ah = to_rah(ibah);

	rxe_drop_ref(ah);
}