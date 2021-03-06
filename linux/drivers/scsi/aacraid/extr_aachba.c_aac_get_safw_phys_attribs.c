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
typedef  int /*<<< orphan*/  u32 ;
struct aac_dev {TYPE_2__* safw_phys_luns; } ;
struct TYPE_4__ {TYPE_1__* lun; } ;
struct TYPE_3__ {int /*<<< orphan*/ * node_ident; } ;

/* Variables and functions */

__attribute__((used)) static inline u32 aac_get_safw_phys_attribs(struct aac_dev *dev, int lun)
{
	return dev->safw_phys_luns->lun[lun].node_ident[9];
}