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
typedef  int u64 ;
typedef  int u32 ;
struct meta_data_on_disk {int /*<<< orphan*/  al_stripe_size_4k; int /*<<< orphan*/  al_stripes; } ;
struct drbd_md {int al_stripe_size_4k; int al_stripes; int al_size_4k; } ;
struct drbd_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int MD_32kB_SECT ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drbd_err (struct drbd_device*,char*,int,int) ; 

__attribute__((used)) static int check_activity_log_stripe_size(struct drbd_device *device,
		struct meta_data_on_disk *on_disk,
		struct drbd_md *in_core)
{
	u32 al_stripes = be32_to_cpu(on_disk->al_stripes);
	u32 al_stripe_size_4k = be32_to_cpu(on_disk->al_stripe_size_4k);
	u64 al_size_4k;

	/* both not set: default to old fixed size activity log */
	if (al_stripes == 0 && al_stripe_size_4k == 0) {
		al_stripes = 1;
		al_stripe_size_4k = MD_32kB_SECT/8;
	}

	/* some paranoia plausibility checks */

	/* we need both values to be set */
	if (al_stripes == 0 || al_stripe_size_4k == 0)
		goto err;

	al_size_4k = (u64)al_stripes * al_stripe_size_4k;

	/* Upper limit of activity log area, to avoid potential overflow
	 * problems in al_tr_number_to_on_disk_sector(). As right now, more
	 * than 72 * 4k blocks total only increases the amount of history,
	 * limiting this arbitrarily to 16 GB is not a real limitation ;-)  */
	if (al_size_4k > (16 * 1024 * 1024/4))
		goto err;

	/* Lower limit: we need at least 8 transaction slots (32kB)
	 * to not break existing setups */
	if (al_size_4k < MD_32kB_SECT/8)
		goto err;

	in_core->al_stripe_size_4k = al_stripe_size_4k;
	in_core->al_stripes = al_stripes;
	in_core->al_size_4k = al_size_4k;

	return 0;
err:
	drbd_err(device, "invalid activity log striping: al_stripes=%u, al_stripe_size_4k=%u\n",
			al_stripes, al_stripe_size_4k);
	return -EINVAL;
}