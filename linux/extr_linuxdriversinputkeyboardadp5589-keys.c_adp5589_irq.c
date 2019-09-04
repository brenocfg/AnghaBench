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
struct i2c_client {int /*<<< orphan*/  dev; } ;
struct adp5589_kpad {int /*<<< orphan*/  input; struct i2c_client* client; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ADP5589_5_INT_STATUS ; 
 int /*<<< orphan*/  ADP5589_5_STATUS ; 
 int EVENT_INT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int KEC ; 
 int OVRFLOW_INT ; 
 int adp5589_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adp5589_report_events (struct adp5589_kpad*,int) ; 
 int /*<<< orphan*/  adp5589_write (struct i2c_client*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  input_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t adp5589_irq(int irq, void *handle)
{
	struct adp5589_kpad *kpad = handle;
	struct i2c_client *client = kpad->client;
	int status, ev_cnt;

	status = adp5589_read(client, ADP5589_5_INT_STATUS);

	if (status & OVRFLOW_INT)	/* Unlikely and should never happen */
		dev_err(&client->dev, "Event Overflow Error\n");

	if (status & EVENT_INT) {
		ev_cnt = adp5589_read(client, ADP5589_5_STATUS) & KEC;
		if (ev_cnt) {
			adp5589_report_events(kpad, ev_cnt);
			input_sync(kpad->input);
		}
	}

	adp5589_write(client, ADP5589_5_INT_STATUS, status); /* Status is W1C */

	return IRQ_HANDLED;
}