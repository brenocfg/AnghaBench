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
struct ipuv3_channel {int num; } ;
struct ipu_soc {int dummy; } ;
typedef  enum ipu_channel_irq { ____Placeholder_ipu_channel_irq } ipu_channel_irq ;

/* Variables and functions */
 int ipu_map_irq (struct ipu_soc*,int) ; 

int ipu_idmac_channel_irq(struct ipu_soc *ipu, struct ipuv3_channel *channel,
		enum ipu_channel_irq irq_type)
{
	return ipu_map_irq(ipu, irq_type + channel->num);
}