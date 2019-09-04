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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct spi_device {int dummy; } ;
struct device {int dummy; } ;
struct ads7846 {int /*<<< orphan*/  lock; } ;
struct ads7845_ser_req {int /*<<< orphan*/ * sample; int /*<<< orphan*/  msg; TYPE_1__* xfer; scalar_t__* command; } ;
struct TYPE_2__ {int len; int /*<<< orphan*/ * rx_buf; scalar_t__* tx_buf; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ads7846_restart (struct ads7846*) ; 
 int /*<<< orphan*/  ads7846_stop (struct ads7846*) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 struct ads7846* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  kfree (struct ads7845_ser_req*) ; 
 struct ads7845_ser_req* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_add_tail (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_init (int /*<<< orphan*/ *) ; 
 int spi_sync (struct spi_device*,int /*<<< orphan*/ *) ; 
 struct spi_device* to_spi_device (struct device*) ; 

__attribute__((used)) static int ads7845_read12_ser(struct device *dev, unsigned command)
{
	struct spi_device *spi = to_spi_device(dev);
	struct ads7846 *ts = dev_get_drvdata(dev);
	struct ads7845_ser_req *req;
	int status;

	req = kzalloc(sizeof *req, GFP_KERNEL);
	if (!req)
		return -ENOMEM;

	spi_message_init(&req->msg);

	req->command[0] = (u8) command;
	req->xfer[0].tx_buf = req->command;
	req->xfer[0].rx_buf = req->sample;
	req->xfer[0].len = 3;
	spi_message_add_tail(&req->xfer[0], &req->msg);

	mutex_lock(&ts->lock);
	ads7846_stop(ts);
	status = spi_sync(spi, &req->msg);
	ads7846_restart(ts);
	mutex_unlock(&ts->lock);

	if (status == 0) {
		/* BE12 value, then padding */
		status = be16_to_cpu(*((u16 *)&req->sample[1]));
		status = status >> 3;
		status &= 0x0fff;
	}

	kfree(req);
	return status;
}