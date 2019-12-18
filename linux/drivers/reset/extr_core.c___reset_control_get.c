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
struct reset_control {int dummy; } ;
struct device {scalar_t__ of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct reset_control* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 struct reset_control* __of_reset_control_get (scalar_t__,char const*,int,int,int,int) ; 
 struct reset_control* __reset_control_get_from_lookup (struct device*,char const*,int,int,int) ; 

struct reset_control *__reset_control_get(struct device *dev, const char *id,
					  int index, bool shared, bool optional,
					  bool acquired)
{
	if (WARN_ON(shared && acquired))
		return ERR_PTR(-EINVAL);

	if (dev->of_node)
		return __of_reset_control_get(dev->of_node, id, index, shared,
					      optional, acquired);

	return __reset_control_get_from_lookup(dev, id, shared, optional,
					       acquired);
}