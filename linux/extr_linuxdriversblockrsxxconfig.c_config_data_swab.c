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
typedef  int /*<<< orphan*/  u32 ;
struct rsxx_card_cfg {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int /*<<< orphan*/  swab32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void config_data_swab(struct rsxx_card_cfg *cfg)
{
	u32 *data = (u32 *) &cfg->data;
	int i;

	for (i = 0; i < (sizeof(cfg->data) / 4); i++)
		data[i] = swab32(data[i]);
}