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
struct wlandevice {int dummy; } ;
struct hfa384x_inf_frame {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void prism2sta_inf_handover(struct wlandevice *wlandev,
				   struct hfa384x_inf_frame *inf)
{
	pr_debug("received infoframe:HANDOVER (unhandled)\n");
}