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
struct delta_dev {scalar_t__ nb_of_decoders; int /*<<< orphan*/  dev; TYPE_1__** decoders; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__**) ; 
 scalar_t__ DELTA_MAX_DECODERS ; 
 int /*<<< orphan*/  DELTA_PREFIX ; 
 TYPE_1__** delta_decoders ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void register_decoders(struct delta_dev *delta)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(delta_decoders); i++) {
		if (delta->nb_of_decoders >= DELTA_MAX_DECODERS) {
			dev_dbg(delta->dev,
				"%s failed to register %s decoder (%d maximum reached)\n",
				DELTA_PREFIX, delta_decoders[i]->name,
				DELTA_MAX_DECODERS);
			return;
		}

		delta->decoders[delta->nb_of_decoders++] = delta_decoders[i];
		dev_info(delta->dev, "%s %s decoder registered\n",
			 DELTA_PREFIX, delta_decoders[i]->name);
	}
}