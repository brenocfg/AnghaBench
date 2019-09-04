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
struct fmr2 {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  io; int /*<<< orphan*/  tea; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct fmr2*) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_tea575x_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fmr2_remove(struct fmr2 *fmr2)
{
	snd_tea575x_exit(&fmr2->tea);
	release_region(fmr2->io, 2);
	v4l2_device_unregister(&fmr2->v4l2_dev);
	kfree(fmr2);
}