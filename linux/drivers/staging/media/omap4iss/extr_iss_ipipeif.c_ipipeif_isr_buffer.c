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
struct TYPE_2__ {int /*<<< orphan*/  dmaqueue; } ;
struct iss_ipipeif_device {TYPE_1__ video_out; } ;
struct iss_buffer {int /*<<< orphan*/  iss_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipipeif_set_outaddr (struct iss_ipipeif_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipipeif_write_enable (struct iss_ipipeif_device*,int) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct iss_buffer* omap4iss_video_buffer_next (TYPE_1__*) ; 

__attribute__((used)) static void ipipeif_isr_buffer(struct iss_ipipeif_device *ipipeif)
{
	struct iss_buffer *buffer;

	/* The ISIF generates VD0 interrupts even when writes are disabled.
	 * deal with it anyway). Disabling the ISIF when no buffer is available
	 * is thus not be enough, we need to handle the situation explicitly.
	 */
	if (list_empty(&ipipeif->video_out.dmaqueue))
		return;

	ipipeif_write_enable(ipipeif, 0);

	buffer = omap4iss_video_buffer_next(&ipipeif->video_out);
	if (!buffer)
		return;

	ipipeif_set_outaddr(ipipeif, buffer->iss_addr);

	ipipeif_write_enable(ipipeif, 1);
}