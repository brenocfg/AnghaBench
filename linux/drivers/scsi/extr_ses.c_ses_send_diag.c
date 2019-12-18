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
typedef  int u32 ;
struct scsi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int SEND_DIAGNOSTIC ; 
 int /*<<< orphan*/  SES_RETRIES ; 
 int /*<<< orphan*/  SES_TIMEOUT ; 
 int scsi_execute_req (struct scsi_device*,unsigned char*,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdev_printk (int /*<<< orphan*/ ,struct scsi_device*,char*,int) ; 

__attribute__((used)) static int ses_send_diag(struct scsi_device *sdev, int page_code,
			 void *buf, int bufflen)
{
	u32 result;

	unsigned char cmd[] = {
		SEND_DIAGNOSTIC,
		0x10,		/* Set PF bit */
		0,
		bufflen >> 8,
		bufflen & 0xff,
		0
	};

	result = scsi_execute_req(sdev, cmd, DMA_TO_DEVICE, buf, bufflen,
				  NULL, SES_TIMEOUT, SES_RETRIES, NULL);
	if (result)
		sdev_printk(KERN_ERR, sdev, "SEND DIAGNOSTIC result: %8x\n",
			    result);
	return result;
}