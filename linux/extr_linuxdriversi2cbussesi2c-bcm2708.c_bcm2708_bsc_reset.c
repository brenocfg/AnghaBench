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
struct bcm2708_i2c {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSC_C ; 
 int /*<<< orphan*/  BSC_S ; 
 int BSC_S_CLKT ; 
 int BSC_S_DONE ; 
 int BSC_S_ERR ; 
 int /*<<< orphan*/  bcm2708_wr (struct bcm2708_i2c*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void bcm2708_bsc_reset(struct bcm2708_i2c *bi)
{
	bcm2708_wr(bi, BSC_C, 0);
	bcm2708_wr(bi, BSC_S, BSC_S_CLKT | BSC_S_ERR | BSC_S_DONE);
}