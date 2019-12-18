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
struct tun_struct {int flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  security; } ;
struct tun_file {struct tun_struct* detached; int /*<<< orphan*/  tun; } ;
struct ifreq {int ifr_flags; } ;
struct file {struct tun_file* private_data; } ;

/* Variables and functions */
 int EINVAL ; 
 int IFF_ATTACH_QUEUE ; 
 int IFF_DETACH_QUEUE ; 
 int IFF_MULTI_QUEUE ; 
 int IFF_NAPI ; 
 int IFF_NAPI_FRAGS ; 
 int /*<<< orphan*/  __tun_detach (struct tun_file*,int) ; 
 int /*<<< orphan*/  netdev_state_change (int /*<<< orphan*/ ) ; 
 struct tun_struct* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int security_tun_dev_attach_queue (int /*<<< orphan*/ ) ; 
 int tun_attach (struct tun_struct*,struct file*,int,int,int,int) ; 

__attribute__((used)) static int tun_set_queue(struct file *file, struct ifreq *ifr)
{
	struct tun_file *tfile = file->private_data;
	struct tun_struct *tun;
	int ret = 0;

	rtnl_lock();

	if (ifr->ifr_flags & IFF_ATTACH_QUEUE) {
		tun = tfile->detached;
		if (!tun) {
			ret = -EINVAL;
			goto unlock;
		}
		ret = security_tun_dev_attach_queue(tun->security);
		if (ret < 0)
			goto unlock;
		ret = tun_attach(tun, file, false, tun->flags & IFF_NAPI,
				 tun->flags & IFF_NAPI_FRAGS, true);
	} else if (ifr->ifr_flags & IFF_DETACH_QUEUE) {
		tun = rtnl_dereference(tfile->tun);
		if (!tun || !(tun->flags & IFF_MULTI_QUEUE) || tfile->detached)
			ret = -EINVAL;
		else
			__tun_detach(tfile, false);
	} else
		ret = -EINVAL;

	if (ret >= 0)
		netdev_state_change(tun->dev);

unlock:
	rtnl_unlock();
	return ret;
}