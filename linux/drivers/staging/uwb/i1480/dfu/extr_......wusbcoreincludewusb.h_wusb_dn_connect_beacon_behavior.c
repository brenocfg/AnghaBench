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
struct wusb_dn_connect {int /*<<< orphan*/  attributes; } ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int wusb_dn_connect_beacon_behavior(const struct wusb_dn_connect *dn)
{
	return (le16_to_cpu(dn->attributes) >> 9) & 0x03;
}