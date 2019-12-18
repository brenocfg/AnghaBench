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
struct mlx4_ib_fmr {int /*<<< orphan*/  mfmr; } ;
struct mlx4_ib_dev {int /*<<< orphan*/  dev; } ;
struct ib_fmr {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct mlx4_ib_fmr*) ; 
 int mlx4_fmr_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct mlx4_ib_dev* to_mdev (int /*<<< orphan*/ ) ; 
 struct mlx4_ib_fmr* to_mfmr (struct ib_fmr*) ; 

int mlx4_ib_fmr_dealloc(struct ib_fmr *ibfmr)
{
	struct mlx4_ib_fmr *ifmr = to_mfmr(ibfmr);
	struct mlx4_ib_dev *dev = to_mdev(ibfmr->device);
	int err;

	err = mlx4_fmr_free(dev->dev, &ifmr->mfmr);

	if (!err)
		kfree(ifmr);

	return err;
}