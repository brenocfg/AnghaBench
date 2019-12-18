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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  core_id; } ;
struct komeda_dev {TYPE_1__ chip; } ;

/* Variables and functions */
 scalar_t__ MALIDP_CORE_ID_PRODUCT_ID (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool
komeda_product_match(struct komeda_dev *mdev, u32 target)
{
	return MALIDP_CORE_ID_PRODUCT_ID(mdev->chip.core_id) == target;
}