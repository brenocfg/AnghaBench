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
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct lima_ip {scalar_t__ id; TYPE_2__ data; struct lima_device* dev; } ;
struct lima_device {int /*<<< orphan*/  dev; TYPE_1__* ip; } ;
struct TYPE_3__ {scalar_t__ present; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  LIMA_L2_CACHE_ENABLE ; 
 int LIMA_L2_CACHE_ENABLE_ACCESS ; 
 int LIMA_L2_CACHE_ENABLE_READ_ALLOCATE ; 
 int /*<<< orphan*/  LIMA_L2_CACHE_MAX_READS ; 
 int /*<<< orphan*/  LIMA_L2_CACHE_SIZE ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int l2_cache_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  l2_cache_write (int /*<<< orphan*/ ,int) ; 
 scalar_t__ lima_ip_l2_cache2 ; 
 int lima_ip_pp4 ; 
 int lima_ip_pp7 ; 
 int lima_l2_cache_flush (struct lima_ip*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int lima_l2_cache_init(struct lima_ip *ip)
{
	int i, err;
	u32 size;
	struct lima_device *dev = ip->dev;

	/* l2_cache2 only exists when one of PP4-7 present */
	if (ip->id == lima_ip_l2_cache2) {
		for (i = lima_ip_pp4; i <= lima_ip_pp7; i++) {
			if (dev->ip[i].present)
				break;
		}
		if (i > lima_ip_pp7)
			return -ENODEV;
	}

	spin_lock_init(&ip->data.lock);

	size = l2_cache_read(LIMA_L2_CACHE_SIZE);
	dev_info(dev->dev, "l2 cache %uK, %u-way, %ubyte cache line, %ubit external bus\n",
		 1 << (((size >> 16) & 0xff) - 10),
		 1 << ((size >> 8) & 0xff),
		 1 << (size & 0xff),
		 1 << ((size >> 24) & 0xff));

	err = lima_l2_cache_flush(ip);
	if (err)
		return err;

	l2_cache_write(LIMA_L2_CACHE_ENABLE,
		       LIMA_L2_CACHE_ENABLE_ACCESS|LIMA_L2_CACHE_ENABLE_READ_ALLOCATE);
	l2_cache_write(LIMA_L2_CACHE_MAX_READS, 0x1c);

	return 0;
}