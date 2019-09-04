#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ssc_device {TYPE_2__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENOTSUPP ; 
 scalar_t__ of_property_read_bool (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static inline int ssc_sound_dai_probe(struct ssc_device *ssc)
{
	if (of_property_read_bool(ssc->pdev->dev.of_node, "#sound-dai-cells"))
		return -ENOTSUPP;

	return 0;
}