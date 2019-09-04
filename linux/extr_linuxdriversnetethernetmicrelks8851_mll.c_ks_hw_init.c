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
struct type_frame_head {int dummy; } ;
struct ks_net {int /*<<< orphan*/  frame_head_info; TYPE_1__* pdev; scalar_t__ mcast_lst_size; scalar_t__ all_mcast; scalar_t__ promiscuous; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KS_DEFAULT_MAC_ADDRESS ; 
 int MAX_RECV_FRAMES ; 
 int /*<<< orphan*/  devm_kmalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ks_set_mac (struct ks_net*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ks_hw_init(struct ks_net *ks)
{
#define	MHEADER_SIZE	(sizeof(struct type_frame_head) * MAX_RECV_FRAMES)
	ks->promiscuous = 0;
	ks->all_mcast = 0;
	ks->mcast_lst_size = 0;

	ks->frame_head_info = devm_kmalloc(&ks->pdev->dev, MHEADER_SIZE,
					   GFP_KERNEL);
	if (!ks->frame_head_info)
		return false;

	ks_set_mac(ks, KS_DEFAULT_MAC_ADDRESS);
	return true;
}