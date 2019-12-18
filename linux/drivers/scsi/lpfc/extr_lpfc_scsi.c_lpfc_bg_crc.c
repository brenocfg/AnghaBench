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
typedef  int /*<<< orphan*/  uint16_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crc_t10dif (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static uint16_t
lpfc_bg_crc(uint8_t *data, int count)
{
	uint16_t crc = 0;
	uint16_t x;

	crc = crc_t10dif(data, count);
	x = cpu_to_be16(crc);
	return x;
}