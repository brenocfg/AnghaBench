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
struct r1conf {int dummy; } ;
struct mddev {struct r1conf* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  freeze_array (struct r1conf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unfreeze_array (struct r1conf*) ; 

__attribute__((used)) static void raid1_quiesce(struct mddev *mddev, int quiesce)
{
	struct r1conf *conf = mddev->private;

	if (quiesce)
		freeze_array(conf, 0);
	else
		unfreeze_array(conf);
}