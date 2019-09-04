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
struct spi_message {int dummy; } ;
struct TYPE_3__ {int ignore; } ;
struct ads7846_packet {TYPE_1__ tc; } ;
struct ads7846 {int msg_count; int (* filter ) (int /*<<< orphan*/ ,int,int*) ;int /*<<< orphan*/  filter_data; TYPE_2__* spi; struct spi_message* msg; int /*<<< orphan*/  (* wait_for_sync ) () ;struct ads7846_packet* packet; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  ADS7846_FILTER_IGNORE 130 
#define  ADS7846_FILTER_OK 129 
#define  ADS7846_FILTER_REPEAT 128 
 int /*<<< orphan*/  BUG () ; 
 int ads7846_get_value (struct ads7846*,struct spi_message*) ; 
 int /*<<< orphan*/  ads7846_update_value (struct spi_message*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int spi_sync (TYPE_2__*,struct spi_message*) ; 
 int /*<<< orphan*/  stub1 () ; 
 int stub2 (int /*<<< orphan*/ ,int,int*) ; 

__attribute__((used)) static void ads7846_read_state(struct ads7846 *ts)
{
	struct ads7846_packet *packet = ts->packet;
	struct spi_message *m;
	int msg_idx = 0;
	int val;
	int action;
	int error;

	while (msg_idx < ts->msg_count) {

		ts->wait_for_sync();

		m = &ts->msg[msg_idx];
		error = spi_sync(ts->spi, m);
		if (error) {
			dev_err(&ts->spi->dev, "spi_sync --> %d\n", error);
			packet->tc.ignore = true;
			return;
		}

		/*
		 * Last message is power down request, no need to convert
		 * or filter the value.
		 */
		if (msg_idx < ts->msg_count - 1) {

			val = ads7846_get_value(ts, m);

			action = ts->filter(ts->filter_data, msg_idx, &val);
			switch (action) {
			case ADS7846_FILTER_REPEAT:
				continue;

			case ADS7846_FILTER_IGNORE:
				packet->tc.ignore = true;
				msg_idx = ts->msg_count - 1;
				continue;

			case ADS7846_FILTER_OK:
				ads7846_update_value(m, val);
				packet->tc.ignore = false;
				msg_idx++;
				break;

			default:
				BUG();
			}
		} else {
			msg_idx++;
		}
	}
}