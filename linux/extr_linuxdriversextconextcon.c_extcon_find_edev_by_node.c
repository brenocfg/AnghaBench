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
struct extcon_dev {int dummy; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSYS ; 
 struct extcon_dev* ERR_PTR (int /*<<< orphan*/ ) ; 

struct extcon_dev *extcon_find_edev_by_node(struct device_node *node)
{
	return ERR_PTR(-ENOSYS);
}