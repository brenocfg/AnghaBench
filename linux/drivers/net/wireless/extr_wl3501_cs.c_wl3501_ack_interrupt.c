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
struct wl3501_card {scalar_t__ base_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  WL3501_GCR_ECINT ; 
 scalar_t__ WL3501_NIC_GCR ; 
 int /*<<< orphan*/  wl3501_outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void wl3501_ack_interrupt(struct wl3501_card *this)
{
	wl3501_outb(WL3501_GCR_ECINT, this->base_addr + WL3501_NIC_GCR);
}