#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct esp {TYPE_1__* target; } ;
struct TYPE_2__ {int /*<<< orphan*/  esp_config3; } ;

/* Variables and functions */
 int ESP_MAX_TARGET ; 

__attribute__((used)) static void esp_set_all_config3(struct esp *esp, u8 val)
{
	int i;

	for (i = 0; i < ESP_MAX_TARGET; i++)
		esp->target[i].esp_config3 = val;
}