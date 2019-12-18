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
struct scatterlist {int dummy; } ;
struct rtsx_ucr {int /*<<< orphan*/  pusb_dev; } ;

/* Variables and functions */
 int rtsx_usb_bulk_transfer_sglist (struct rtsx_ucr*,unsigned int,struct scatterlist*,int,unsigned int,unsigned int*,int) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,unsigned int,void*,unsigned int,unsigned int*,int) ; 

int rtsx_usb_transfer_data(struct rtsx_ucr *ucr, unsigned int pipe,
			      void *buf, unsigned int len, int num_sg,
			      unsigned int *act_len, int timeout)
{
	if (timeout < 600)
		timeout = 600;

	if (num_sg)
		return rtsx_usb_bulk_transfer_sglist(ucr, pipe,
				(struct scatterlist *)buf, num_sg, len, act_len,
				timeout);
	else
		return usb_bulk_msg(ucr->pusb_dev, pipe, buf, len, act_len,
				timeout);
}