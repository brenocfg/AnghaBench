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
struct platform_device {int dummy; } ;
struct pcap_ts {int /*<<< orphan*/  input; int /*<<< orphan*/  work; int /*<<< orphan*/  pcap; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_IRQ_TS ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pcap_ts*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pcap_ts*) ; 
 int /*<<< orphan*/  pcap_to_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pcap_ts* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int pcap_ts_remove(struct platform_device *pdev)
{
	struct pcap_ts *pcap_ts = platform_get_drvdata(pdev);

	free_irq(pcap_to_irq(pcap_ts->pcap, PCAP_IRQ_TS), pcap_ts);
	cancel_delayed_work_sync(&pcap_ts->work);

	input_unregister_device(pcap_ts->input);

	kfree(pcap_ts);

	return 0;
}