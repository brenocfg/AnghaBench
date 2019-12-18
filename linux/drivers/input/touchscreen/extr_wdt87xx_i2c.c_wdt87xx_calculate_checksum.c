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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  misr (int /*<<< orphan*/ ,int /*<<< orphan*/  const) ; 

__attribute__((used)) static u16 wdt87xx_calculate_checksum(const u8 *data, size_t length)
{
	u16 checksum = 0;
	size_t i;

	for (i = 0; i < length; i++)
		checksum = misr(checksum, data[i]);

	return checksum;
}