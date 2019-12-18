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
typedef  int u16 ;
struct uwb_ie_drp {int /*<<< orphan*/  drp_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void uwb_ie_drp_set_unsafe(struct uwb_ie_drp *ie, int unsafe)
{
	u16 drp_control = le16_to_cpu(ie->drp_control);
	drp_control = (drp_control & ~(0x1 << 12)) | (unsafe << 12);
	ie->drp_control = cpu_to_le16(drp_control);
}