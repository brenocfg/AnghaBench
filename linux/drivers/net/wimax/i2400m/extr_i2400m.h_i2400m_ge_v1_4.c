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
struct i2400m {int fw_version; } ;

/* Variables and functions */

__attribute__((used)) static inline
unsigned i2400m_ge_v1_4(struct i2400m *i2400m)
{
	/* running fw is higher or v1.4 */
	return i2400m->fw_version >= 0x00090002;
}