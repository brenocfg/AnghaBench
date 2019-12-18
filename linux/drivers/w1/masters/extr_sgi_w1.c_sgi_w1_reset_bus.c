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
struct sgi_w1_device {int /*<<< orphan*/  mcr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCR_PACK (int,int) ; 
 int /*<<< orphan*/  sgi_w1_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u8 sgi_w1_reset_bus(void *data)
{
	struct sgi_w1_device *dev = data;
	u8 ret;

	writel(MCR_PACK(520, 65), dev->mcr);
	ret = sgi_w1_wait(dev->mcr);
	udelay(500); /* recovery time */
	return ret;
}