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
typedef  int u32 ;
struct aac_dev {TYPE_1__* safw_phys_luns; } ;
struct TYPE_2__ {int /*<<< orphan*/ * list_length; } ;

/* Variables and functions */
 int get_unaligned_be32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline u32 aac_get_safw_phys_lun_count(struct aac_dev *dev)
{
	return get_unaligned_be32(&dev->safw_phys_luns->list_length[0])/24;
}