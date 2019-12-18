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
struct ntb_dev {int dummy; } ;
struct idt_ntb_dev {int peer_cnt; } ;

/* Variables and functions */
 struct idt_ntb_dev* to_ndev_ntb (struct ntb_dev*) ; 

__attribute__((used)) static int idt_ntb_peer_port_count(struct ntb_dev *ntb)
{
	struct idt_ntb_dev *ndev = to_ndev_ntb(ntb);

	return ndev->peer_cnt;
}