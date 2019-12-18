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
typedef  int /*<<< orphan*/  uint8_t ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  sil164_read (struct i2c_client*,int) ; 

__attribute__((used)) static void
sil164_save_state(struct i2c_client *client, uint8_t *state)
{
	int i;

	for (i = 0x8; i <= 0xe; i++)
		state[i] = sil164_read(client, i);
}