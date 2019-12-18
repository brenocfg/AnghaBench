#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int value; scalar_t__ disabled; } ;
union iwreq_data {TYPE_2__ frag; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_3__ {int frag_len; } ;
struct _adapter {TYPE_1__ xmitpriv; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_FRAG_THRESHOLD ; 
 int MIN_FRAG_THRESHOLD ; 
 struct _adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int r8711_wx_set_frag(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	struct _adapter *padapter = netdev_priv(dev);

	if (wrqu->frag.disabled) {
		padapter->xmitpriv.frag_len = MAX_FRAG_THRESHOLD;
	} else {
		if (wrqu->frag.value < MIN_FRAG_THRESHOLD ||
		    wrqu->frag.value > MAX_FRAG_THRESHOLD)
			return -EINVAL;
		padapter->xmitpriv.frag_len = wrqu->frag.value & ~0x1;
	}
	return 0;
}