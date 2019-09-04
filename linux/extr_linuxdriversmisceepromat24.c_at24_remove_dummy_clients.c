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
struct at24_data {int num_addresses; TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2c_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void at24_remove_dummy_clients(struct at24_data *at24)
{
	int i;

	for (i = 1; i < at24->num_addresses; i++)
		i2c_unregister_device(at24->client[i].client);
}