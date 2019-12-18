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
struct r8152 {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  RTL8152_UNPLUG ; 
 int rtl_enable (struct r8152*) ; 
 int /*<<< orphan*/  rtl_set_eee_plus (struct r8152*) ; 
 int /*<<< orphan*/  set_tx_qlen (struct r8152*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rtl8152_enable(struct r8152 *tp)
{
	if (test_bit(RTL8152_UNPLUG, &tp->flags))
		return -ENODEV;

	set_tx_qlen(tp);
	rtl_set_eee_plus(tp);

	return rtl_enable(tp);
}