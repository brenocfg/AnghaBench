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

/* Variables and functions */
 int /*<<< orphan*/  I2400M_NBOOT_BARKER ; 
 int /*<<< orphan*/  I2400M_SBOOT_BARKER ; 
 int /*<<< orphan*/  I2400M_SBOOT_BARKER_6050 ; 
 int i2400m_barker_db_add (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int i2400m_barker_db_known_barkers(void)
{
	int result;

	result = i2400m_barker_db_add(I2400M_NBOOT_BARKER);
	if (result < 0)
		goto error_add;
	result = i2400m_barker_db_add(I2400M_SBOOT_BARKER);
	if (result < 0)
		goto error_add;
	result = i2400m_barker_db_add(I2400M_SBOOT_BARKER_6050);
	if (result < 0)
		goto error_add;
error_add:
       return result;
}