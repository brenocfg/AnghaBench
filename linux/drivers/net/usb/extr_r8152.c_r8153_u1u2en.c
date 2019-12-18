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
typedef  int /*<<< orphan*/  u1u2 ;
struct r8152 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BYTE_EN_SIX_BYTES ; 
 int /*<<< orphan*/  USB_TOLERANCE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  usb_ocp_write (struct r8152*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void r8153_u1u2en(struct r8152 *tp, bool enable)
{
	u8 u1u2[8];

	if (enable)
		memset(u1u2, 0xff, sizeof(u1u2));
	else
		memset(u1u2, 0x00, sizeof(u1u2));

	usb_ocp_write(tp, USB_TOLERANCE, BYTE_EN_SIX_BYTES, sizeof(u1u2), u1u2);
}