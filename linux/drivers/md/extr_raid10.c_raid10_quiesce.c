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
struct r10conf {int dummy; } ;
struct mddev {struct r10conf* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  lower_barrier (struct r10conf*) ; 
 int /*<<< orphan*/  raise_barrier (struct r10conf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void raid10_quiesce(struct mddev *mddev, int quiesce)
{
	struct r10conf *conf = mddev->private;

	if (quiesce)
		raise_barrier(conf, 0);
	else
		lower_barrier(conf);
}