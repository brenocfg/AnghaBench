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
struct sk_buff {int dummy; } ;
struct nci_dev {int dummy; } ;
typedef  enum s3fwrn5_mode { ____Placeholder_s3fwrn5_mode } s3fwrn5_mode ;

/* Variables and functions */
 int ENODEV ; 
#define  S3FWRN5_MODE_FW 129 
#define  S3FWRN5_MODE_NCI 128 
 int nci_recv_frame (struct nci_dev*,struct sk_buff*) ; 
 int s3fwrn5_fw_recv_frame (struct nci_dev*,struct sk_buff*) ; 

int s3fwrn5_recv_frame(struct nci_dev *ndev, struct sk_buff *skb,
	enum s3fwrn5_mode mode)
{
	switch (mode) {
	case S3FWRN5_MODE_NCI:
		return nci_recv_frame(ndev, skb);
	case S3FWRN5_MODE_FW:
		return s3fwrn5_fw_recv_frame(ndev, skb);
	default:
		return -ENODEV;
	}
}