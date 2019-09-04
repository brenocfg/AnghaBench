#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int udp_encap; } ;
struct ocrdma_dev {TYPE_1__ attr; } ;

/* Variables and functions */
 int OCRDMA_L3_TYPE_IPV4 ; 
 int OCRDMA_L3_TYPE_IPV6 ; 

__attribute__((used)) static inline bool ocrdma_is_udp_encap_supported(struct ocrdma_dev *dev)
{
	return (dev->attr.udp_encap & OCRDMA_L3_TYPE_IPV4) ||
	       (dev->attr.udp_encap & OCRDMA_L3_TYPE_IPV6);
}