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
struct pvr2_hdw {scalar_t__ cropcap_stale; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  pvr2_hdw_status_poll (struct pvr2_hdw*) ; 

__attribute__((used)) static int pvr2_hdw_check_cropcap(struct pvr2_hdw *hdw)
{
	if (!hdw->cropcap_stale) {
		return 0;
	}
	pvr2_hdw_status_poll(hdw);
	if (hdw->cropcap_stale) {
		return -EIO;
	}
	return 0;
}