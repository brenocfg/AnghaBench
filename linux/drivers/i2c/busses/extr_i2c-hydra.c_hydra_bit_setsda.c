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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  HYDRA_SDAT ; 
 int /*<<< orphan*/  HYDRA_SDAT_OE ; 
 int /*<<< orphan*/  pdregr (void*) ; 
 int /*<<< orphan*/  pdregw (void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hydra_bit_setsda(void *data, int state)
{
	u32 val = pdregr(data);
	if (state)
		val &= ~HYDRA_SDAT_OE;
	else {
		val &= ~HYDRA_SDAT;
		val |= HYDRA_SDAT_OE;
	}
	pdregw(data, val);
}