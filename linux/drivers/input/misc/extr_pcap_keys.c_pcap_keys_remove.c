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
struct pcap_keys {int /*<<< orphan*/  input; int /*<<< orphan*/  pcap; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCAP_IRQ_MIC ; 
 int /*<<< orphan*/  PCAP_IRQ_ONOFF ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pcap_keys*) ; 
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct pcap_keys*) ; 
 int /*<<< orphan*/  pcap_to_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct pcap_keys* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int pcap_keys_remove(struct platform_device *pdev)
{
	struct pcap_keys *pcap_keys = platform_get_drvdata(pdev);

	free_irq(pcap_to_irq(pcap_keys->pcap, PCAP_IRQ_ONOFF), pcap_keys);
	free_irq(pcap_to_irq(pcap_keys->pcap, PCAP_IRQ_MIC), pcap_keys);

	input_unregister_device(pcap_keys->input);
	kfree(pcap_keys);

	return 0;
}