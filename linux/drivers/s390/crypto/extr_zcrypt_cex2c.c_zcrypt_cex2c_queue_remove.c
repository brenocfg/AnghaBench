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
struct zcrypt_queue {int dummy; } ;
struct ap_queue {struct zcrypt_queue* private; } ;
struct ap_device {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 struct ap_queue* to_ap_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zcrypt_queue_unregister (struct zcrypt_queue*) ; 

__attribute__((used)) static void zcrypt_cex2c_queue_remove(struct ap_device *ap_dev)
{
	struct ap_queue *aq = to_ap_queue(&ap_dev->device);
	struct zcrypt_queue *zq = aq->private;

	if (zq)
		zcrypt_queue_unregister(zq);
}