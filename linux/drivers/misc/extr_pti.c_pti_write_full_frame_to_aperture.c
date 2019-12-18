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
typedef  int /*<<< orphan*/  u8 ;
struct pti_masterchannel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pti_control_frame_built_and_sent (struct pti_masterchannel*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pti_write_to_aperture (struct pti_masterchannel*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void pti_write_full_frame_to_aperture(struct pti_masterchannel *mc,
						const unsigned char *buf,
						int len)
{
	pti_control_frame_built_and_sent(mc, NULL);
	pti_write_to_aperture(mc, (u8 *)buf, len);
}