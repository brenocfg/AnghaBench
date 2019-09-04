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
typedef  int u8 ;
struct zforce_ts {int boot_complete; int version_major; int version_minor; int version_build; int version_rev; scalar_t__ suspending; struct i2c_client* client; int /*<<< orphan*/  gpio_int; scalar_t__ suspended; } ;
struct i2c_client {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int FRAME_MAXSIZE ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
#define  NOTIFICATION_BOOTCOMPLETE 136 
#define  NOTIFICATION_INVALID_COMMAND 135 
#define  NOTIFICATION_TOUCH 134 
 size_t PAYLOAD_BODY ; 
 size_t RESPONSE_DATA ; 
#define  RESPONSE_DEACTIVATE 133 
 size_t RESPONSE_ID ; 
#define  RESPONSE_INITIALIZE 132 
#define  RESPONSE_RESOLUTION 131 
#define  RESPONSE_SCANFREQ 130 
#define  RESPONSE_SETCONFIG 129 
#define  RESPONSE_STATUS 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ device_may_wakeup (int /*<<< orphan*/ *) ; 
 scalar_t__ gpiod_get_value_cansleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  pm_relax (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_stay_awake (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_wakeup_event (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zforce_complete (struct zforce_ts*,int,int) ; 
 int zforce_read_packet (struct zforce_ts*,int*) ; 
 int /*<<< orphan*/  zforce_touch_event (struct zforce_ts*,int*) ; 

__attribute__((used)) static irqreturn_t zforce_irq_thread(int irq, void *dev_id)
{
	struct zforce_ts *ts = dev_id;
	struct i2c_client *client = ts->client;
	int ret;
	u8 payload_buffer[FRAME_MAXSIZE];
	u8 *payload;

	/*
	 * When still suspended, return.
	 * Due to the level-interrupt we will get re-triggered later.
	 */
	if (ts->suspended) {
		msleep(20);
		return IRQ_HANDLED;
	}

	dev_dbg(&client->dev, "handling interrupt\n");

	/* Don't emit wakeup events from commands run by zforce_suspend */
	if (!ts->suspending && device_may_wakeup(&client->dev))
		pm_stay_awake(&client->dev);

	/*
	 * Run at least once and exit the loop if
	 * - the optional interrupt GPIO isn't specified
	 *   (there is only one packet read per ISR invocation, then)
	 * or
	 * - the GPIO isn't active any more
	 *   (packet read until the level GPIO indicates that there is
	 *    no IRQ any more)
	 */
	do {
		ret = zforce_read_packet(ts, payload_buffer);
		if (ret < 0) {
			dev_err(&client->dev,
				"could not read packet, ret: %d\n", ret);
			break;
		}

		payload =  &payload_buffer[PAYLOAD_BODY];

		switch (payload[RESPONSE_ID]) {
		case NOTIFICATION_TOUCH:
			/*
			 * Always report touch-events received while
			 * suspending, when being a wakeup source
			 */
			if (ts->suspending && device_may_wakeup(&client->dev))
				pm_wakeup_event(&client->dev, 500);
			zforce_touch_event(ts, &payload[RESPONSE_DATA]);
			break;

		case NOTIFICATION_BOOTCOMPLETE:
			ts->boot_complete = payload[RESPONSE_DATA];
			zforce_complete(ts, payload[RESPONSE_ID], 0);
			break;

		case RESPONSE_INITIALIZE:
		case RESPONSE_DEACTIVATE:
		case RESPONSE_SETCONFIG:
		case RESPONSE_RESOLUTION:
		case RESPONSE_SCANFREQ:
			zforce_complete(ts, payload[RESPONSE_ID],
					payload[RESPONSE_DATA]);
			break;

		case RESPONSE_STATUS:
			/*
			 * Version Payload Results
			 * [2:major] [2:minor] [2:build] [2:rev]
			 */
			ts->version_major = (payload[RESPONSE_DATA + 1] << 8) |
						payload[RESPONSE_DATA];
			ts->version_minor = (payload[RESPONSE_DATA + 3] << 8) |
						payload[RESPONSE_DATA + 2];
			ts->version_build = (payload[RESPONSE_DATA + 5] << 8) |
						payload[RESPONSE_DATA + 4];
			ts->version_rev   = (payload[RESPONSE_DATA + 7] << 8) |
						payload[RESPONSE_DATA + 6];
			dev_dbg(&ts->client->dev,
				"Firmware Version %04x:%04x %04x:%04x\n",
				ts->version_major, ts->version_minor,
				ts->version_build, ts->version_rev);

			zforce_complete(ts, payload[RESPONSE_ID], 0);
			break;

		case NOTIFICATION_INVALID_COMMAND:
			dev_err(&ts->client->dev, "invalid command: 0x%x\n",
				payload[RESPONSE_DATA]);
			break;

		default:
			dev_err(&ts->client->dev,
				"unrecognized response id: 0x%x\n",
				payload[RESPONSE_ID]);
			break;
		}
	} while (gpiod_get_value_cansleep(ts->gpio_int));

	if (!ts->suspending && device_may_wakeup(&client->dev))
		pm_relax(&client->dev);

	dev_dbg(&client->dev, "finished interrupt\n");

	return IRQ_HANDLED;
}