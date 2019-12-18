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
struct sge {int /*<<< orphan*/  fl_align; scalar_t__ pktshift; } ;
struct adapter {struct sge sge; } ;

/* Variables and functions */
 unsigned int ALIGN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ETH_HLEN ; 
 scalar_t__ VLAN_HLEN ; 

__attribute__((used)) static inline unsigned int fl_mtu_bufsize(struct adapter *adapter,
					  unsigned int mtu)
{
	struct sge *s = &adapter->sge;

	return ALIGN(s->pktshift + ETH_HLEN + VLAN_HLEN + mtu, s->fl_align);
}