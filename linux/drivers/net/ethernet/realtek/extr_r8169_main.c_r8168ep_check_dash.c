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
struct rtl8169_private {int dummy; } ;

/* Variables and functions */
 int r8168ep_ocp_read (struct rtl8169_private*,int,int) ; 

__attribute__((used)) static bool r8168ep_check_dash(struct rtl8169_private *tp)
{
	return !!(r8168ep_ocp_read(tp, 0x0f, 0x128) & 0x00000001);
}