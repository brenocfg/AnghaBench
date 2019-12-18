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
struct nfc_mei_phy {int /*<<< orphan*/  send_wq; struct mei_cl_device* cldev; } ;
struct mei_cl_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct nfc_mei_phy* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mei_cldev_set_drvdata (struct mei_cl_device*,struct nfc_mei_phy*) ; 

struct nfc_mei_phy *nfc_mei_phy_alloc(struct mei_cl_device *cldev)
{
	struct nfc_mei_phy *phy;

	phy = kzalloc(sizeof(struct nfc_mei_phy), GFP_KERNEL);
	if (!phy)
		return NULL;

	phy->cldev = cldev;
	init_waitqueue_head(&phy->send_wq);
	mei_cldev_set_drvdata(cldev, phy);

	return phy;
}