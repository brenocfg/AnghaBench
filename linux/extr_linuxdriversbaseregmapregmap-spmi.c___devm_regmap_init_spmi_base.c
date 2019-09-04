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
struct spmi_device {int /*<<< orphan*/  dev; } ;
struct regmap_config {int dummy; } ;
struct regmap {int dummy; } ;
struct lock_class_key {int dummy; } ;

/* Variables and functions */
 struct regmap* __devm_regmap_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct spmi_device*,struct regmap_config const*,struct lock_class_key*,char const*) ; 
 int /*<<< orphan*/  regmap_spmi_base ; 

struct regmap *__devm_regmap_init_spmi_base(struct spmi_device *sdev,
					    const struct regmap_config *config,
					    struct lock_class_key *lock_key,
					    const char *lock_name)
{
	return __devm_regmap_init(&sdev->dev, &regmap_spmi_base, sdev, config,
				  lock_key, lock_name);
}