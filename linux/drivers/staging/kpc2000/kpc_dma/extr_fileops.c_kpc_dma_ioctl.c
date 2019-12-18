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
struct file {scalar_t__ private_data; } ;
struct dev_private_data {unsigned long card_addr; unsigned long user_ctl; unsigned long user_ctl_last; long user_sts; } ;

/* Variables and functions */
 long ENOTTY ; 
#define  KND_IOCTL_GET_USER_STS 131 
#define  KND_IOCTL_SET_CARD_ADDR 130 
#define  KND_IOCTL_SET_USER_CTL 129 
#define  KND_IOCTL_SET_USER_CTL_LAST 128 

__attribute__((used)) static
long  kpc_dma_ioctl(struct file *filp, unsigned int ioctl_num, unsigned long ioctl_param)
{
	struct dev_private_data *priv = (struct dev_private_data *)filp->private_data;

	switch (ioctl_num) {
	case KND_IOCTL_SET_CARD_ADDR:
		priv->card_addr  = ioctl_param; return priv->card_addr;
	case KND_IOCTL_SET_USER_CTL:
		priv->user_ctl   = ioctl_param; return priv->user_ctl;
	case KND_IOCTL_SET_USER_CTL_LAST:
		priv->user_ctl_last = ioctl_param; return priv->user_ctl_last;
	case KND_IOCTL_GET_USER_STS:
		return priv->user_sts;
	}

	return -ENOTTY;
}