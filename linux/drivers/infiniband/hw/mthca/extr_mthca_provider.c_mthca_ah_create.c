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
struct rdma_ah_attr {int dummy; } ;
struct mthca_ah {int dummy; } ;
struct ib_udata {int dummy; } ;
struct ib_ah {int /*<<< orphan*/  pd; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int mthca_create_ah (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rdma_ah_attr*,struct mthca_ah*) ; 
 struct mthca_ah* to_mah (struct ib_ah*) ; 
 int /*<<< orphan*/  to_mdev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_mpd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mthca_ah_create(struct ib_ah *ibah, struct rdma_ah_attr *ah_attr,
			   u32 flags, struct ib_udata *udata)

{
	struct mthca_ah *ah = to_mah(ibah);

	return mthca_create_ah(to_mdev(ibah->device), to_mpd(ibah->pd), ah_attr,
			       ah);
}