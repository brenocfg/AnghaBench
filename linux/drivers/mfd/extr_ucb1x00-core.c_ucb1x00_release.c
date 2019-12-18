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
struct ucb1x00 {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct ucb1x00* classdev_to_ucb1x00 (struct device*) ; 
 int /*<<< orphan*/  kfree (struct ucb1x00*) ; 

__attribute__((used)) static void ucb1x00_release(struct device *dev)
{
	struct ucb1x00 *ucb = classdev_to_ucb1x00(dev);
	kfree(ucb);
}