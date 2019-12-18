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
typedef  int u32 ;
struct iss_ipipeif_device {int output; int /*<<< orphan*/  stopping; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int IPIPEIF_OUTPUT_MEMORY ; 
 int ISP5_IRQ_ISIF_INT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipipeif_isr_buffer (struct iss_ipipeif_device*) ; 
 scalar_t__ omap4iss_module_sync_is_stopping (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void omap4iss_ipipeif_isr(struct iss_ipipeif_device *ipipeif, u32 events)
{
	if (omap4iss_module_sync_is_stopping(&ipipeif->wait,
					     &ipipeif->stopping))
		return;

	if ((events & ISP5_IRQ_ISIF_INT(0)) &&
	    (ipipeif->output & IPIPEIF_OUTPUT_MEMORY))
		ipipeif_isr_buffer(ipipeif);
}