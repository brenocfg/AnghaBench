#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_4__ {int /*<<< orphan*/  data_base_addr; } ;
struct rmi_function {TYPE_1__ fd; int /*<<< orphan*/  dev; struct rmi_device* rmi_dev; } ;
struct TYPE_5__ {int size; scalar_t__ data; } ;
struct rmi_driver_data {TYPE_2__ attn_data; } ;
struct rmi_device {int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {int pkt_size; int attn_size; int /*<<< orphan*/  data_pkt; } ;
struct f11_data {TYPE_3__ sensor; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 void* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  rmi_f11_finger_handler (struct f11_data*,TYPE_3__*,int) ; 
 int rmi_read_block (struct rmi_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t rmi_f11_attention(int irq, void *ctx)
{
	struct rmi_function *fn = ctx;
	struct rmi_device *rmi_dev = fn->rmi_dev;
	struct rmi_driver_data *drvdata = dev_get_drvdata(&rmi_dev->dev);
	struct f11_data *f11 = dev_get_drvdata(&fn->dev);
	u16 data_base_addr = fn->fd.data_base_addr;
	int error;
	int valid_bytes = f11->sensor.pkt_size;

	if (drvdata->attn_data.data) {
		/*
		 * The valid data in the attention report is less then
		 * expected. Only process the complete fingers.
		 */
		if (f11->sensor.attn_size > drvdata->attn_data.size)
			valid_bytes = drvdata->attn_data.size;
		else
			valid_bytes = f11->sensor.attn_size;
		memcpy(f11->sensor.data_pkt, drvdata->attn_data.data,
			valid_bytes);
		drvdata->attn_data.data += valid_bytes;
		drvdata->attn_data.size -= valid_bytes;
	} else {
		error = rmi_read_block(rmi_dev,
				data_base_addr, f11->sensor.data_pkt,
				f11->sensor.pkt_size);
		if (error < 0)
			return IRQ_RETVAL(error);
	}

	rmi_f11_finger_handler(f11, &f11->sensor, valid_bytes);

	return IRQ_HANDLED;
}