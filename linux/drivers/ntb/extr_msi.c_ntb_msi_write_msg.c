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
struct ntb_msi_devres {TYPE_2__* ntb; int /*<<< orphan*/  msi_desc; } ;
struct msi_desc {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  ctx; TYPE_1__* msi; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* desc_changed ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntb_msi_set_desc (TYPE_2__*,struct msi_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ntb_msi_write_msg(struct msi_desc *entry, void *data)
{
	struct ntb_msi_devres *dr = data;

	WARN_ON(ntb_msi_set_desc(dr->ntb, entry, dr->msi_desc));

	if (dr->ntb->msi->desc_changed)
		dr->ntb->msi->desc_changed(dr->ntb->ctx);
}