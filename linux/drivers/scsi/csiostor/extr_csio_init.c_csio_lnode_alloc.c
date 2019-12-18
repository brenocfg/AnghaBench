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
struct csio_lnode {int dummy; } ;
struct csio_hw {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 struct csio_lnode* csio_shost_init (struct csio_hw*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

struct csio_lnode *
csio_lnode_alloc(struct csio_hw *hw)
{
	return csio_shost_init(hw, &hw->pdev->dev, false, NULL);
}