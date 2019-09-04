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
struct snd_ac97 {int /*<<< orphan*/  dev; } ;
struct regmap_config {int dummy; } ;
struct regmap {int dummy; } ;
struct lock_class_key {int dummy; } ;

/* Variables and functions */
 struct regmap* __devm_regmap_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct snd_ac97*,struct regmap_config const*,struct lock_class_key*,char const*) ; 
 int /*<<< orphan*/  ac97_regmap_bus ; 

struct regmap *__devm_regmap_init_ac97(struct snd_ac97 *ac97,
				       const struct regmap_config *config,
				       struct lock_class_key *lock_key,
				       const char *lock_name)
{
	return __devm_regmap_init(&ac97->dev, &ac97_regmap_bus, ac97, config,
				  lock_key, lock_name);
}