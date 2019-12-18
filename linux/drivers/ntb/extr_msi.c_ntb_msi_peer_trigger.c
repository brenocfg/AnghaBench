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
struct ntb_msi_desc {int addr_offset; int /*<<< orphan*/  data; } ;
struct ntb_dev {TYPE_1__* msi; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** peer_mws; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ntb_msi_peer_trigger(struct ntb_dev *ntb, int peer,
			 struct ntb_msi_desc *desc)
{
	int idx;

	if (!ntb->msi)
		return -EINVAL;

	idx = desc->addr_offset / sizeof(*ntb->msi->peer_mws[peer]);

	iowrite32(desc->data, &ntb->msi->peer_mws[peer][idx]);

	return 0;
}