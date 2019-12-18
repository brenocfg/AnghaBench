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
struct net_device {int mtu; } ;
struct TYPE_3__ {unsigned int icv_len; } ;
struct macsec_dev {TYPE_2__* real_dev; TYPE_1__ secy; } ;
struct TYPE_4__ {unsigned int mtu; } ;

/* Variables and functions */
 int ERANGE ; 
 unsigned int macsec_extra_len (int) ; 
 struct macsec_dev* macsec_priv (struct net_device*) ; 

__attribute__((used)) static int macsec_change_mtu(struct net_device *dev, int new_mtu)
{
	struct macsec_dev *macsec = macsec_priv(dev);
	unsigned int extra = macsec->secy.icv_len + macsec_extra_len(true);

	if (macsec->real_dev->mtu - extra < new_mtu)
		return -ERANGE;

	dev->mtu = new_mtu;

	return 0;
}