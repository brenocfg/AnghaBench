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
struct ucsi_connector {int /*<<< orphan*/  work; } ;
struct ucsi_cci {int connector_change; scalar_t__ ack_complete; scalar_t__ cmd_complete; scalar_t__ busy; scalar_t__ error; } ;
struct ucsi {TYPE_2__* ppm; int /*<<< orphan*/  flags; struct ucsi_connector* connector; int /*<<< orphan*/  complete; int /*<<< orphan*/  status; } ;
struct TYPE_4__ {TYPE_1__* data; } ;
struct TYPE_3__ {int /*<<< orphan*/  raw_cci; struct ucsi_cci cci; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACK_PENDING ; 
 int /*<<< orphan*/  COMMAND_PENDING ; 
 int /*<<< orphan*/  EVENT_PENDING ; 
 int /*<<< orphan*/  UCSI_BUSY ; 
 int /*<<< orphan*/  UCSI_ERROR ; 
 int /*<<< orphan*/  UCSI_IDLE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ucsi_notify (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucsi_sync (struct ucsi*) ; 

void ucsi_notify(struct ucsi *ucsi)
{
	struct ucsi_cci *cci;

	/* There is no requirement to sync here, but no harm either. */
	ucsi_sync(ucsi);

	cci = &ucsi->ppm->data->cci;

	if (cci->error)
		ucsi->status = UCSI_ERROR;
	else if (cci->busy)
		ucsi->status = UCSI_BUSY;
	else
		ucsi->status = UCSI_IDLE;

	if (cci->cmd_complete && test_bit(COMMAND_PENDING, &ucsi->flags)) {
		complete(&ucsi->complete);
	} else if (cci->ack_complete && test_bit(ACK_PENDING, &ucsi->flags)) {
		complete(&ucsi->complete);
	} else if (cci->connector_change) {
		struct ucsi_connector *con;

		con = &ucsi->connector[cci->connector_change - 1];

		if (!test_and_set_bit(EVENT_PENDING, &ucsi->flags))
			schedule_work(&con->work);
	}

	trace_ucsi_notify(ucsi->ppm->data->raw_cci);
}