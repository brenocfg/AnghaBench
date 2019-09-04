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
struct mpcc {int dummy; } ;
struct mpc {struct mpcc* mpcc_array; } ;
struct dcn10_mpc {int num_mpcc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 struct dcn10_mpc* TO_DCN10_MPC (struct mpc*) ; 

struct mpcc *mpc1_get_mpcc(struct mpc *mpc, int mpcc_id)
{
	struct dcn10_mpc *mpc10 = TO_DCN10_MPC(mpc);

	ASSERT(mpcc_id < mpc10->num_mpcc);
	return &(mpc->mpcc_array[mpcc_id]);
}