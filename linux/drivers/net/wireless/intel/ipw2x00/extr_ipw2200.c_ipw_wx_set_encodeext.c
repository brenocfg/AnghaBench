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
typedef  union iwreq_data {int dummy; } iwreq_data ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_encode_ext {scalar_t__ alg; int ext_flags; } ;
struct ipw_priv {TYPE_1__* ieee; } ;
struct TYPE_2__ {int host_mc_decrypt; int host_encrypt_msdu; int host_decrypt; scalar_t__ host_encrypt; } ;

/* Variables and functions */
 scalar_t__ IW_ENCODE_ALG_TKIP ; 
 int IW_ENCODE_EXT_GROUP_KEY ; 
 scalar_t__ hwcrypto ; 
 struct ipw_priv* libipw_priv (struct net_device*) ; 
 int libipw_wx_set_encodeext (TYPE_1__*,struct iw_request_info*,union iwreq_data*,char*) ; 

__attribute__((used)) static int ipw_wx_set_encodeext(struct net_device *dev,
				struct iw_request_info *info,
				union iwreq_data *wrqu, char *extra)
{
	struct ipw_priv *priv = libipw_priv(dev);
	struct iw_encode_ext *ext = (struct iw_encode_ext *)extra;

	if (hwcrypto) {
		if (ext->alg == IW_ENCODE_ALG_TKIP) {
			/* IPW HW can't build TKIP MIC,
			   host decryption still needed */
			if (ext->ext_flags & IW_ENCODE_EXT_GROUP_KEY)
				priv->ieee->host_mc_decrypt = 1;
			else {
				priv->ieee->host_encrypt = 0;
				priv->ieee->host_encrypt_msdu = 1;
				priv->ieee->host_decrypt = 1;
			}
		} else {
			priv->ieee->host_encrypt = 0;
			priv->ieee->host_encrypt_msdu = 0;
			priv->ieee->host_decrypt = 0;
			priv->ieee->host_mc_decrypt = 0;
		}
	}

	return libipw_wx_set_encodeext(priv->ieee, info, wrqu, extra);
}