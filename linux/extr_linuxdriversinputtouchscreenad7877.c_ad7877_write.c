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
typedef  int u16 ;
struct spi_device {int dummy; } ;
struct ser_req {int command; int /*<<< orphan*/  msg; TYPE_1__* xfer; } ;
struct TYPE_2__ {int* tx_buf; int len; } ;

/* Variables and functions */
 int AD7877_WRITEADD (int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MAX_12BIT ; 
 int /*<<< orphan*/  kfree (struct ser_req*) ; 
 struct ser_req* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spi_message_add_tail (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spi_message_init (int /*<<< orphan*/ *) ; 
 int spi_sync (struct spi_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ad7877_write(struct spi_device *spi, u16 reg, u16 val)
{
	struct ser_req *req;
	int status;

	req = kzalloc(sizeof *req, GFP_KERNEL);
	if (!req)
		return -ENOMEM;

	spi_message_init(&req->msg);

	req->command = (u16) (AD7877_WRITEADD(reg) | (val & MAX_12BIT));
	req->xfer[0].tx_buf = &req->command;
	req->xfer[0].len = 2;

	spi_message_add_tail(&req->xfer[0], &req->msg);

	status = spi_sync(spi, &req->msg);

	kfree(req);

	return status;
}