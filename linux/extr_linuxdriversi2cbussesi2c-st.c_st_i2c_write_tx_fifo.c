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
typedef  int u16 ;
struct st_i2c_dev {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ SSC_TBUF ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static inline void st_i2c_write_tx_fifo(struct st_i2c_dev *i2c_dev, u8 byte)
{
	u16 tbuf = byte << 1;

	writel_relaxed(tbuf | 1, i2c_dev->base + SSC_TBUF);
}