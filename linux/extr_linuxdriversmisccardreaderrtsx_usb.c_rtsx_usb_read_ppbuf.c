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
typedef  int /*<<< orphan*/  u16 ;
struct rtsx_ucr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPBUF_BASE2 ; 
 int rtsx_usb_seq_read_register (struct rtsx_ucr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int rtsx_usb_read_ppbuf(struct rtsx_ucr *ucr, u8 *buf, int buf_len)
{
	return rtsx_usb_seq_read_register(ucr, PPBUF_BASE2, (u16)buf_len, buf);
}