#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bcm2708_i2c {scalar_t__ pos; TYPE_1__* msg; } ;
struct TYPE_2__ {scalar_t__ len; int* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  BSC_FIFO ; 
 int /*<<< orphan*/  BSC_S ; 
 int BSC_S_RXD ; 
 int bcm2708_rd (struct bcm2708_i2c*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void bcm2708_bsc_fifo_drain(struct bcm2708_i2c *bi)
{
	while ((bi->pos < bi->msg->len) && (bcm2708_rd(bi, BSC_S) & BSC_S_RXD))
		bi->msg->buf[bi->pos++] = bcm2708_rd(bi, BSC_FIFO);
}