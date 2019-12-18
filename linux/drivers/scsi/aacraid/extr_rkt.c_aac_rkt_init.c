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
struct TYPE_2__ {int /*<<< orphan*/  adapter_comm; int /*<<< orphan*/  adapter_ioremap; } ;
struct aac_dev {TYPE_1__ a_ops; } ;

/* Variables and functions */
 int _aac_rx_init (struct aac_dev*) ; 
 int /*<<< orphan*/  aac_rkt_ioremap ; 
 int /*<<< orphan*/  aac_rkt_select_comm ; 

int aac_rkt_init(struct aac_dev *dev)
{
	/*
	 *	Fill in the function dispatch table.
	 */
	dev->a_ops.adapter_ioremap = aac_rkt_ioremap;
	dev->a_ops.adapter_comm = aac_rkt_select_comm;

	return _aac_rx_init(dev);
}