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
struct sk_buff {int queue_mapping; } ;
struct octeon_device {int num_iqs; } ;

/* Variables and functions */

__attribute__((used)) static inline int skb_iq(struct octeon_device *oct, struct sk_buff *skb)
{
	return skb->queue_mapping % oct->num_iqs;
}