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
typedef  int u8 ;

/* Variables and functions */

__attribute__((used)) static inline void rvu_get_cgx_lmac_id(u8 map, u8 *cgx_id, u8 *lmac_id)
{
	*cgx_id = (map >> 4) & 0xF;
	*lmac_id = (map & 0xF);
}