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
typedef  int u32 ;
struct bcm2835_host {int dummy; } ;

/* Variables and functions */
 int bcm2835_mmc_readl (struct bcm2835_host*,int) ; 

__attribute__((used)) static inline u8 bcm2835_mmc_readb(struct bcm2835_host *host, int reg)
{
	u32 val = bcm2835_mmc_readl(host, (reg & ~3));
	u32 byte_num = reg & 3;
	u32 byte_shift = byte_num * 8;
	u32 byte = (val >> byte_shift) & 0xff;

	return byte;
}