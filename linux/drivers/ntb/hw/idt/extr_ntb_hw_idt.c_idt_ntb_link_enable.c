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
struct ntb_dev {int dummy; } ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct idt_ntb_dev {TYPE_2__ ntb; } ;
typedef  enum ntb_width { ____Placeholder_ntb_width } ntb_width ;
typedef  enum ntb_speed { ____Placeholder_ntb_speed } ntb_speed ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  idt_ntb_local_link_enable (struct idt_ntb_dev*) ; 
 struct idt_ntb_dev* to_ndev_ntb (struct ntb_dev*) ; 

__attribute__((used)) static int idt_ntb_link_enable(struct ntb_dev *ntb, enum ntb_speed speed,
			       enum ntb_width width)
{
	struct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	/* Just enable the local NTB link */
	idt_ntb_local_link_enable(ndev);

	dev_dbg(&ndev->ntb.pdev->dev, "Local NTB link enabled");

	return 0;
}