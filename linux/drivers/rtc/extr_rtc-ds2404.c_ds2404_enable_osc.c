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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ds2404_write_memory (struct device*,int,int,int*) ; 

__attribute__((used)) static void ds2404_enable_osc(struct device *dev)
{
	u8 in[1] = { 0x10 }; /* enable oscillator */
	ds2404_write_memory(dev, 0x201, 1, in);
}