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
struct sja1105_l2_policing_entry {int sharindx; int smax; scalar_t__ partition; scalar_t__ maxlen; int /*<<< orphan*/  rate; } ;

/* Variables and functions */
 scalar_t__ ETH_FCS_LEN ; 
 scalar_t__ ETH_FRAME_LEN ; 
 int /*<<< orphan*/  SJA1105_RATE_MBPS (int) ; 
 scalar_t__ VLAN_HLEN ; 

__attribute__((used)) static inline void
sja1105_setup_policer(struct sja1105_l2_policing_entry *policing,
		      int index)
{
	policing[index].sharindx = index;
	policing[index].smax = 65535; /* Burst size in bytes */
	policing[index].rate = SJA1105_RATE_MBPS(1000);
	policing[index].maxlen = ETH_FRAME_LEN + VLAN_HLEN + ETH_FCS_LEN;
	policing[index].partition = 0;
}