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
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int flags; int value; scalar_t__ disabled; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  HFA384X_RID_CNFMAXSLEEPDURATION ; 
 int /*<<< orphan*/  HFA384X_RID_CNFMULTICASTRECEIVE ; 
 int /*<<< orphan*/  HFA384X_RID_CNFPMENABLED ; 
 int /*<<< orphan*/  HFA384X_RID_CNFPMHOLDOVERDURATION ; 
#define  IW_POWER_ALL_R 130 
 int IW_POWER_MODE ; 
#define  IW_POWER_ON 129 
 int IW_POWER_PERIOD ; 
 int IW_POWER_TIMEOUT ; 
#define  IW_POWER_UNICAST_R 128 
 int hostap_set_word (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int prism2_ioctl_siwpower(struct net_device *dev,
				 struct iw_request_info *info,
				 struct iw_param *wrq, char *extra)
{
#ifdef PRISM2_NO_STATION_MODES
	return -EOPNOTSUPP;
#else /* PRISM2_NO_STATION_MODES */
	int ret = 0;

	if (wrq->disabled)
		return hostap_set_word(dev, HFA384X_RID_CNFPMENABLED, 0);

	switch (wrq->flags & IW_POWER_MODE) {
	case IW_POWER_UNICAST_R:
		ret = hostap_set_word(dev, HFA384X_RID_CNFMULTICASTRECEIVE, 0);
		if (ret)
			return ret;
		ret = hostap_set_word(dev, HFA384X_RID_CNFPMENABLED, 1);
		if (ret)
			return ret;
		break;
	case IW_POWER_ALL_R:
		ret = hostap_set_word(dev, HFA384X_RID_CNFMULTICASTRECEIVE, 1);
		if (ret)
			return ret;
		ret = hostap_set_word(dev, HFA384X_RID_CNFPMENABLED, 1);
		if (ret)
			return ret;
		break;
	case IW_POWER_ON:
		break;
	default:
		return -EINVAL;
	}

	if (wrq->flags & IW_POWER_TIMEOUT) {
		ret = hostap_set_word(dev, HFA384X_RID_CNFPMENABLED, 1);
		if (ret)
			return ret;
		ret = hostap_set_word(dev, HFA384X_RID_CNFPMHOLDOVERDURATION,
				      wrq->value / 1024);
		if (ret)
			return ret;
	}
	if (wrq->flags & IW_POWER_PERIOD) {
		ret = hostap_set_word(dev, HFA384X_RID_CNFPMENABLED, 1);
		if (ret)
			return ret;
		ret = hostap_set_word(dev, HFA384X_RID_CNFMAXSLEEPDURATION,
				      wrq->value / 1024);
		if (ret)
			return ret;
	}

	return ret;
#endif /* PRISM2_NO_STATION_MODES */
}