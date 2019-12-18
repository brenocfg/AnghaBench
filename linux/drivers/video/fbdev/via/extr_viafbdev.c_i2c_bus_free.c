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
struct viafb_shared {int /*<<< orphan*/  i2c_2C; int /*<<< orphan*/  i2c_31; int /*<<< orphan*/  i2c_26; } ;

/* Variables and functions */
 int /*<<< orphan*/  via_aux_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void i2c_bus_free(struct viafb_shared *shared)
{
	via_aux_free(shared->i2c_26);
	via_aux_free(shared->i2c_31);
	via_aux_free(shared->i2c_2C);
}