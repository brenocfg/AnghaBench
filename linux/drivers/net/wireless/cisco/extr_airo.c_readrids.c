#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {struct airo_info* ml_priv; } ;
struct airo_info {unsigned char micstats; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int command; int len; unsigned short ridnum; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ aironet_ioctl ;

/* Variables and functions */
#define  AIROGCAP 140 
#define  AIROGCFG 139 
#define  AIROGDRVNAM 138 
#define  AIROGEHTENC 137 
#define  AIROGMICSTATS 136 
#define  AIROGSLIST 135 
#define  AIROGSTAT 134 
#define  AIROGSTATSC32 133 
#define  AIROGSTATSD32 132 
#define  AIROGVLIST 131 
#define  AIROGWEPKNV 130 
#define  AIROGWEPKTMP 129 
#define  AIRORRID 128 
 int /*<<< orphan*/  CAP_NET_ADMIN ; 
 int EFAULT ; 
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int EPERM ; 
 int /*<<< orphan*/  FLAG_COMMIT ; 
 int /*<<< orphan*/  FLAG_FLASHING ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PC4500_readrid (struct airo_info*,unsigned short,unsigned char*,scalar_t__,int) ; 
 scalar_t__ RIDSIZE ; 
 unsigned short RID_APLIST ; 
 unsigned short RID_CAPABILITIES ; 
 unsigned short RID_CONFIG ; 
 unsigned short RID_DRVNAME ; 
 unsigned short RID_ETHERENCAP ; 
 unsigned short RID_SSID ; 
 unsigned short RID_STATS ; 
 unsigned short RID_STATSDELTA ; 
 unsigned short RID_STATUS ; 
 unsigned short RID_WEP_PERM ; 
 unsigned short RID_WEP_TEMP ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ copy_to_user (int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disable_MAC (struct airo_info*,int) ; 
 int /*<<< orphan*/  enable_MAC (struct airo_info*,int) ; 
 int /*<<< orphan*/  kfree (unsigned char*) ; 
 unsigned char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  min (int,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeConfigRid (struct airo_info*,int) ; 

__attribute__((used)) static int readrids(struct net_device *dev, aironet_ioctl *comp) {
	unsigned short ridcode;
	unsigned char *iobuf;
	int len;
	struct airo_info *ai = dev->ml_priv;

	if (test_bit(FLAG_FLASHING, &ai->flags))
		return -EIO;

	switch(comp->command)
	{
	case AIROGCAP:      ridcode = RID_CAPABILITIES; break;
	case AIROGCFG:      ridcode = RID_CONFIG;
		if (test_bit(FLAG_COMMIT, &ai->flags)) {
			disable_MAC (ai, 1);
			writeConfigRid (ai, 1);
			enable_MAC(ai, 1);
		}
		break;
	case AIROGSLIST:    ridcode = RID_SSID;         break;
	case AIROGVLIST:    ridcode = RID_APLIST;       break;
	case AIROGDRVNAM:   ridcode = RID_DRVNAME;      break;
	case AIROGEHTENC:   ridcode = RID_ETHERENCAP;   break;
	case AIROGWEPKTMP:  ridcode = RID_WEP_TEMP;
		/* Only super-user can read WEP keys */
		if (!capable(CAP_NET_ADMIN))
			return -EPERM;
		break;
	case AIROGWEPKNV:   ridcode = RID_WEP_PERM;
		/* Only super-user can read WEP keys */
		if (!capable(CAP_NET_ADMIN))
			return -EPERM;
		break;
	case AIROGSTAT:     ridcode = RID_STATUS;       break;
	case AIROGSTATSD32: ridcode = RID_STATSDELTA;   break;
	case AIROGSTATSC32: ridcode = RID_STATS;        break;
	case AIROGMICSTATS:
		if (copy_to_user(comp->data, &ai->micstats,
				 min((int)comp->len,(int)sizeof(ai->micstats))))
			return -EFAULT;
		return 0;
	case AIRORRID:      ridcode = comp->ridnum;     break;
	default:
		return -EINVAL;
	}

	if ((iobuf = kmalloc(RIDSIZE, GFP_KERNEL)) == NULL)
		return -ENOMEM;

	PC4500_readrid(ai,ridcode,iobuf,RIDSIZE, 1);
	/* get the count of bytes in the rid  docs say 1st 2 bytes is it.
	 * then return it to the user
	 * 9/22/2000 Honor user given length
	 */
	len = comp->len;

	if (copy_to_user(comp->data, iobuf, min(len, (int)RIDSIZE))) {
		kfree (iobuf);
		return -EFAULT;
	}
	kfree (iobuf);
	return 0;
}