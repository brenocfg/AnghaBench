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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct of_device_id {scalar_t__ data; } ;

/* Variables and functions */
 int EINVAL ; 
 int __schizo_init (struct platform_device*,unsigned long) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schizo_match ; 

__attribute__((used)) static int schizo_probe(struct platform_device *op)
{
	const struct of_device_id *match;

	match = of_match_device(schizo_match, &op->dev);
	if (!match)
		return -EINVAL;
	return __schizo_init(op, (unsigned long)match->data);
}