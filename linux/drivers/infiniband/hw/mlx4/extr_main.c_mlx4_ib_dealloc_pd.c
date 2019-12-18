#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ib_udata {int dummy; } ;
struct ib_pd {int /*<<< orphan*/  device; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  pdn; } ;

/* Variables and functions */
 int /*<<< orphan*/  mlx4_pd_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* to_mdev (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_mpd (struct ib_pd*) ; 

__attribute__((used)) static void mlx4_ib_dealloc_pd(struct ib_pd *pd, struct ib_udata *udata)
{
	mlx4_pd_free(to_mdev(pd->device)->dev, to_mpd(pd)->pdn);
}