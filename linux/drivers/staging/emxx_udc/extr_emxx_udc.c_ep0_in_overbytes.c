#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * DATA; } ;
union usb_reg_access {int /*<<< orphan*/  dw; TYPE_1__ byte; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct nbu2ss_udc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _nbu2ss_ep_in_end (struct nbu2ss_udc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ep0_in_overbytes(struct nbu2ss_udc *udc,
			    u8 *p_buf,
			    u32 i_remain_size)
{
	u32		i;
	union usb_reg_access  temp_32;
	union usb_reg_access  *p_buf_32 = (union usb_reg_access *)p_buf;

	if ((i_remain_size > 0) && (i_remain_size < sizeof(u32))) {
		for (i = 0 ; i < i_remain_size ; i++)
			temp_32.byte.DATA[i] = p_buf_32->byte.DATA[i];
		_nbu2ss_ep_in_end(udc, 0, temp_32.dw, i_remain_size);

		return i_remain_size;
	}

	return 0;
}