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
struct mic_mw {int dummy; } ;
struct mic_device {struct mic_mw aper; } ;
struct cosm_device {int dummy; } ;

/* Variables and functions */
 struct mic_device* cosmdev_to_mdev (struct cosm_device*) ; 

__attribute__((used)) static struct mic_mw *_mic_aper(struct cosm_device *cdev)
{
	struct mic_device *mdev = cosmdev_to_mdev(cdev);

	return &mdev->aper;
}