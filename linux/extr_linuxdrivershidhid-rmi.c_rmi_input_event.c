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
typedef  int /*<<< orphan*/  u8 ;
struct rmi_device {int dummy; } ;
struct TYPE_2__ {struct rmi_device* rmi_dev; } ;
struct rmi_data {int /*<<< orphan*/  rmi_irq; int /*<<< orphan*/  flags; TYPE_1__ xport; } ;
struct hid_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RMI_STARTED ; 
 int /*<<< orphan*/  generic_handle_irq (int /*<<< orphan*/ ) ; 
 struct rmi_data* hid_get_drvdata (struct hid_device*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  rmi_set_attn_data (struct rmi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rmi_input_event(struct hid_device *hdev, u8 *data, int size)
{
	struct rmi_data *hdata = hid_get_drvdata(hdev);
	struct rmi_device *rmi_dev = hdata->xport.rmi_dev;
	unsigned long flags;

	if (!(test_bit(RMI_STARTED, &hdata->flags)))
		return 0;

	local_irq_save(flags);

	rmi_set_attn_data(rmi_dev, data[1], &data[2], size - 2);

	generic_handle_irq(hdata->rmi_irq);

	local_irq_restore(flags);

	return 1;
}