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
struct i2400m {int /*<<< orphan*/  sboot; } ;

/* Variables and functions */
 int likely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
unsigned i2400m_boot_is_signed(struct i2400m *i2400m)
{
	return likely(i2400m->sboot);
}