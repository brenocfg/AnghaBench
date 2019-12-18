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
struct slim_eaddr {int dummy; } ;
struct slim_device {int /*<<< orphan*/  e_addr; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int slim_eaddr_equal (int /*<<< orphan*/ *,struct slim_eaddr*) ; 
 struct slim_device* to_slim_device (struct device*) ; 

__attribute__((used)) static int slim_match_dev(struct device *dev, void *data)
{
	struct slim_eaddr *e_addr = data;
	struct slim_device *sbdev = to_slim_device(dev);

	return slim_eaddr_equal(&sbdev->e_addr, e_addr);
}