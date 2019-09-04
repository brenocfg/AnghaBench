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
struct pcap_data {int /*<<< orphan*/ * pcap; int /*<<< orphan*/ * compiled; } ;

/* Variables and functions */
 int /*<<< orphan*/  pcap_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pcap_freecode (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pcap_remove(void *data)
{
	struct pcap_data *pri = data;

	if (pri->compiled != NULL)
		pcap_freecode(pri->compiled);

	if (pri->pcap != NULL)
		pcap_close(pri->pcap);
}