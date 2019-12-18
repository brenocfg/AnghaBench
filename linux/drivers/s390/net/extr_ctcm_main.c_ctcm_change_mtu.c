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
struct net_device {int hard_header_len; int mtu; struct ctcm_priv* ml_priv; } ;
struct ctcm_priv {TYPE_1__** channel; } ;
struct TYPE_2__ {int max_bufsize; } ;

/* Variables and functions */
 size_t CTCM_READ ; 
 int EINVAL ; 
 scalar_t__ IS_MPC (struct ctcm_priv*) ; 
 int LL_HEADER_LENGTH ; 
 int PDU_HEADER_LENGTH ; 
 int TH_HEADER_LENGTH ; 

__attribute__((used)) static int ctcm_change_mtu(struct net_device *dev, int new_mtu)
{
	struct ctcm_priv *priv;
	int max_bufsize;

	priv = dev->ml_priv;
	max_bufsize = priv->channel[CTCM_READ]->max_bufsize;

	if (IS_MPC(priv)) {
		if (new_mtu > max_bufsize - TH_HEADER_LENGTH)
			return -EINVAL;
		dev->hard_header_len = TH_HEADER_LENGTH + PDU_HEADER_LENGTH;
	} else {
		if (new_mtu > max_bufsize - LL_HEADER_LENGTH - 2)
			return -EINVAL;
		dev->hard_header_len = LL_HEADER_LENGTH + 2;
	}
	dev->mtu = new_mtu;
	return 0;
}