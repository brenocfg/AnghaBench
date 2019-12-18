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
struct efa_dev {int dummy; } ;

/* Variables and functions */
 int efa_request_mgmnt_irq (struct efa_dev*) ; 
 int /*<<< orphan*/  efa_setup_mgmnt_irq (struct efa_dev*) ; 

__attribute__((used)) static int efa_set_mgmnt_irq(struct efa_dev *dev)
{
	efa_setup_mgmnt_irq(dev);

	return efa_request_mgmnt_irq(dev);
}