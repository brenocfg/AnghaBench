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
struct TYPE_3__ {int supported; int enabled; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* pqi_firmware_features ; 

__attribute__((used)) static void pqi_init_firmware_features(void)
{
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(pqi_firmware_features); i++) {
		pqi_firmware_features[i].supported = false;
		pqi_firmware_features[i].enabled = false;
	}
}