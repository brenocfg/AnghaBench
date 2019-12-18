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
typedef  int u16 ;
struct net_device {scalar_t__ base_addr; } ;

/* Variables and functions */
 scalar_t__ GCR ; 
 int inw (scalar_t__) ; 
 int /*<<< orphan*/  outw (int,scalar_t__) ; 

__attribute__((used)) static void atmel_clear_gcr(struct net_device *dev, u16 mask)
{
	outw(inw(dev->base_addr + GCR) & ~mask, dev->base_addr + GCR);
}