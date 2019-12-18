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
union usb_reg_access {int /*<<< orphan*/  dw; } ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct nbu2ss_udc {TYPE_1__* p_regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  EP0_WRITE; } ;

/* Variables and functions */
 int EP0_PACKETSIZE ; 
 int /*<<< orphan*/  _nbu2ss_writel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int EP0_in_PIO(struct nbu2ss_udc *udc, u8 *p_buf, u32 length)
{
	u32		i;
	u32		i_max_length   = EP0_PACKETSIZE;
	u32		i_word_length  = 0;
	u32		i_write_length = 0;
	union usb_reg_access  *p_buf_32 = (union usb_reg_access *)p_buf;

	/*------------------------------------------------------------*/
	/* Transfer Length */
	if (i_max_length < length)
		i_word_length = i_max_length / sizeof(u32);
	else
		i_word_length = length / sizeof(u32);

	/*------------------------------------------------------------*/
	/* PIO */
	for (i = 0; i < i_word_length; i++) {
		_nbu2ss_writel(&udc->p_regs->EP0_WRITE, p_buf_32->dw);
		p_buf_32++;
		i_write_length += sizeof(u32);
	}

	return i_write_length;
}