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
struct hnae_ae_dev {int dummy; } ;
struct fwnode_handle {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __ae_match ; 
 struct device* class_find_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct fwnode_handle const*,int /*<<< orphan*/ ) ; 
 struct hnae_ae_dev* cls_to_ae_dev (struct device*) ; 
 int /*<<< orphan*/  hnae_class ; 

__attribute__((used)) static struct hnae_ae_dev *find_ae(const struct fwnode_handle *fwnode)
{
	struct device *dev;

	WARN_ON(!fwnode);

	dev = class_find_device(hnae_class, NULL, fwnode, __ae_match);

	return dev ? cls_to_ae_dev(dev) : NULL;
}