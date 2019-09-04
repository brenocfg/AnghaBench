#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hva_dev {scalar_t__ nb_of_encoders; TYPE_1__** encoders; } ;
struct device {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__**) ; 
 scalar_t__ HVA_MAX_ENCODERS ; 
 int /*<<< orphan*/  HVA_PREFIX ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__** hva_encoders ; 
 struct device* hva_to_dev (struct hva_dev*) ; 

__attribute__((used)) static void register_encoders(struct hva_dev *hva)
{
	struct device *dev = hva_to_dev(hva);
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(hva_encoders); i++) {
		if (hva->nb_of_encoders >= HVA_MAX_ENCODERS) {
			dev_dbg(dev,
				"%s failed to register %s encoder (%d maximum reached)\n",
				HVA_PREFIX, hva_encoders[i]->name,
				HVA_MAX_ENCODERS);
			return;
		}

		hva->encoders[hva->nb_of_encoders++] = hva_encoders[i];
		dev_info(dev, "%s %s encoder registered\n", HVA_PREFIX,
			 hva_encoders[i]->name);
	}
}