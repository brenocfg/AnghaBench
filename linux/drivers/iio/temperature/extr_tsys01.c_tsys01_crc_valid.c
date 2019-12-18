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
typedef  scalar_t__ u8 ;
typedef  int u16 ;

/* Variables and functions */
 scalar_t__ TSYS01_PROM_WORDS_NB ; 

__attribute__((used)) static bool tsys01_crc_valid(u16 *n_prom)
{
	u8 cnt;
	u8 sum = 0;

	for (cnt = 0; cnt < TSYS01_PROM_WORDS_NB; cnt++)
		sum += ((n_prom[0] >> 8) + (n_prom[0] & 0xFF));

	return (sum == 0);
}