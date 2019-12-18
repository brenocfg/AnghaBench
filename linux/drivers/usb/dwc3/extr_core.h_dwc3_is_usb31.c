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
struct dwc3 {int revision; } ;

/* Variables and functions */
 int DWC3_REVISION_IS_DWC31 ; 

__attribute__((used)) static inline bool dwc3_is_usb31(struct dwc3 *dwc)
{
	return !!(dwc->revision & DWC3_REVISION_IS_DWC31);
}