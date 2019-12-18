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
struct b53_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ is5325 (struct b53_device*) ; 
 scalar_t__ is5365 (struct b53_device*) ; 

__attribute__((used)) static u16 b53_default_pvid(struct b53_device *dev)
{
	if (is5325(dev) || is5365(dev))
		return 1;
	else
		return 0;
}