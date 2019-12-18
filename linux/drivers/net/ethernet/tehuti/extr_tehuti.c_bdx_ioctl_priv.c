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
struct net_device {int dummy; } ;
struct ifreq {int /*<<< orphan*/  ifr_data; } ;
struct bdx_priv {int dummy; } ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
#define  BDX_OP_READ 129 
#define  BDX_OP_WRITE 128 
 int /*<<< orphan*/  CAP_SYS_RAWIO ; 
 int /*<<< orphan*/  DBG (char*,int,int,...) ; 
 int EFAULT ; 
 int /*<<< orphan*/  ENTER ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int READ_REG (struct bdx_priv*,int) ; 
 int /*<<< orphan*/  RET (int) ; 
 int SIOCDEVPRIVATE ; 
 int /*<<< orphan*/  WRITE_REG (struct bdx_priv*,int,int) ; 
 int bdx_range_check (struct bdx_priv*,int) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int copy_from_user (int*,int /*<<< orphan*/ ,int) ; 
 int copy_to_user (int /*<<< orphan*/ ,int*,int) ; 
 int jiffies ; 
 struct bdx_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int bdx_ioctl_priv(struct net_device *ndev, struct ifreq *ifr, int cmd)
{
	struct bdx_priv *priv = netdev_priv(ndev);
	u32 data[3];
	int error;

	ENTER;

	DBG("jiffies=%ld cmd=%d\n", jiffies, cmd);
	if (cmd != SIOCDEVPRIVATE) {
		error = copy_from_user(data, ifr->ifr_data, sizeof(data));
		if (error) {
			pr_err("can't copy from user\n");
			RET(-EFAULT);
		}
		DBG("%d 0x%x 0x%x\n", data[0], data[1], data[2]);
	} else {
		return -EOPNOTSUPP;
	}

	if (!capable(CAP_SYS_RAWIO))
		return -EPERM;

	switch (data[0]) {

	case BDX_OP_READ:
		error = bdx_range_check(priv, data[1]);
		if (error < 0)
			return error;
		data[2] = READ_REG(priv, data[1]);
		DBG("read_reg(0x%x)=0x%x (dec %d)\n", data[1], data[2],
		    data[2]);
		error = copy_to_user(ifr->ifr_data, data, sizeof(data));
		if (error)
			RET(-EFAULT);
		break;

	case BDX_OP_WRITE:
		error = bdx_range_check(priv, data[1]);
		if (error < 0)
			return error;
		WRITE_REG(priv, data[1], data[2]);
		DBG("write_reg(0x%x, 0x%x)\n", data[1], data[2]);
		break;

	default:
		RET(-EOPNOTSUPP);
	}
	return 0;
}