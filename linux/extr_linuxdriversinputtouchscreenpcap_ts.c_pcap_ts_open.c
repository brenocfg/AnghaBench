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
struct pcap_ts {int /*<<< orphan*/  work; int /*<<< orphan*/  read_state; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_ADC_TS_M_STANDBY ; 
 struct pcap_ts* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pcap_ts_open(struct input_dev *dev)
{
	struct pcap_ts *pcap_ts = input_get_drvdata(dev);

	pcap_ts->read_state = PCAP_ADC_TS_M_STANDBY;
	schedule_delayed_work(&pcap_ts->work, 0);

	return 0;
}