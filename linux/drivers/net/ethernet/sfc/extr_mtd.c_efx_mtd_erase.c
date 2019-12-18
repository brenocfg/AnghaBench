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
struct mtd_info {struct efx_nic* priv; } ;
struct erase_info {int /*<<< orphan*/  len; int /*<<< orphan*/  addr; } ;
struct efx_nic {TYPE_1__* type; } ;
struct TYPE_2__ {int (* mtd_erase ) (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int stub1 (struct mtd_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int efx_mtd_erase(struct mtd_info *mtd, struct erase_info *erase)
{
	struct efx_nic *efx = mtd->priv;

	return efx->type->mtd_erase(mtd, erase->addr, erase->len);
}