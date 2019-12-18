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
struct TYPE_6__ {int size; struct mrq_i2c_response* data; } ;
struct TYPE_5__ {int size; struct mrq_i2c_request* data; } ;
struct tegra_bpmp_message {TYPE_3__ rx; TYPE_2__ tx; int /*<<< orphan*/  mrq; } ;
struct tegra_bpmp_i2c {int /*<<< orphan*/  bpmp; int /*<<< orphan*/  bus; } ;
struct mrq_i2c_response {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus_id; } ;
struct mrq_i2c_request {TYPE_1__ xfer; int /*<<< orphan*/  cmd; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_I2C_XFER ; 
 int /*<<< orphan*/  MRQ_I2C ; 
 int /*<<< orphan*/  memset (struct tegra_bpmp_message*,int /*<<< orphan*/ ,int) ; 
 int tegra_bpmp_transfer (int /*<<< orphan*/ ,struct tegra_bpmp_message*) ; 
 int tegra_bpmp_transfer_atomic (int /*<<< orphan*/ ,struct tegra_bpmp_message*) ; 

__attribute__((used)) static int tegra_bpmp_i2c_msg_xfer(struct tegra_bpmp_i2c *i2c,
				   struct mrq_i2c_request *request,
				   struct mrq_i2c_response *response,
				   bool atomic)
{
	struct tegra_bpmp_message msg;
	int err;

	request->cmd = CMD_I2C_XFER;
	request->xfer.bus_id = i2c->bus;

	memset(&msg, 0, sizeof(msg));
	msg.mrq = MRQ_I2C;
	msg.tx.data = request;
	msg.tx.size = sizeof(*request);
	msg.rx.data = response;
	msg.rx.size = sizeof(*response);

	if (atomic)
		err = tegra_bpmp_transfer_atomic(i2c->bpmp, &msg);
	else
		err = tegra_bpmp_transfer(i2c->bpmp, &msg);

	return err;
}