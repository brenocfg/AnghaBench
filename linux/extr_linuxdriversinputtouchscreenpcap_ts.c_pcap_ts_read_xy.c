#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* u16 ;
struct pcap_ts {int read_state; TYPE_1__* input; int /*<<< orphan*/  work; void* pressure; void* y; void* x; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int /*<<< orphan*/  ABS_X ; 
 int /*<<< orphan*/  ABS_Y ; 
 int /*<<< orphan*/  BTN_TOUCH ; 
#define  PCAP_ADC_TS_M_PRESSURE 129 
 int PCAP_ADC_TS_M_STANDBY ; 
#define  PCAP_ADC_TS_M_XY 128 
 void* PRESSURE_MAX ; 
 void* PRESSURE_MIN ; 
 int /*<<< orphan*/  SAMPLE_DELAY ; 
 void* X_AXIS_MAX ; 
 void* X_AXIS_MIN ; 
 void* Y_AXIS_MAX ; 
 void* Y_AXIS_MIN ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  input_report_abs (TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  input_report_key (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  input_sync (TYPE_1__*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pcap_ts_read_xy(void *data, u16 res[2])
{
	struct pcap_ts *pcap_ts = data;

	switch (pcap_ts->read_state) {
	case PCAP_ADC_TS_M_PRESSURE:
		/* pressure reading is unreliable */
		if (res[0] > PRESSURE_MIN && res[0] < PRESSURE_MAX)
			pcap_ts->pressure = res[0];
		pcap_ts->read_state = PCAP_ADC_TS_M_XY;
		schedule_delayed_work(&pcap_ts->work, 0);
		break;
	case PCAP_ADC_TS_M_XY:
		pcap_ts->y = res[0];
		pcap_ts->x = res[1];
		if (pcap_ts->x <= X_AXIS_MIN || pcap_ts->x >= X_AXIS_MAX ||
		    pcap_ts->y <= Y_AXIS_MIN || pcap_ts->y >= Y_AXIS_MAX) {
			/* pen has been released */
			input_report_abs(pcap_ts->input, ABS_PRESSURE, 0);
			input_report_key(pcap_ts->input, BTN_TOUCH, 0);

			pcap_ts->read_state = PCAP_ADC_TS_M_STANDBY;
			schedule_delayed_work(&pcap_ts->work, 0);
		} else {
			/* pen is touching the screen */
			input_report_abs(pcap_ts->input, ABS_X, pcap_ts->x);
			input_report_abs(pcap_ts->input, ABS_Y, pcap_ts->y);
			input_report_key(pcap_ts->input, BTN_TOUCH, 1);
			input_report_abs(pcap_ts->input, ABS_PRESSURE,
						pcap_ts->pressure);

			/* switch back to pressure read mode */
			pcap_ts->read_state = PCAP_ADC_TS_M_PRESSURE;
			schedule_delayed_work(&pcap_ts->work,
					msecs_to_jiffies(SAMPLE_DELAY));
		}
		input_sync(pcap_ts->input);
		break;
	default:
		dev_warn(&pcap_ts->input->dev,
				"pcap_ts: Warning, unhandled read_state %d\n",
				pcap_ts->read_state);
		break;
	}
}