#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int num_mpts; } ;
struct mlx4_dev {TYPE_1__ caps; } ;

/* Variables and functions */

__attribute__((used)) static int mpt_mask(struct mlx4_dev *dev)
{
	return dev->caps.num_mpts - 1;
}