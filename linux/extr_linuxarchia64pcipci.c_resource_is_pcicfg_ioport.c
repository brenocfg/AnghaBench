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
struct resource {int flags; int start; int end; } ;

/* Variables and functions */
 int IORESOURCE_IO ; 

__attribute__((used)) static bool resource_is_pcicfg_ioport(struct resource *res)
{
	return (res->flags & IORESOURCE_IO) &&
		res->start == 0xCF8 && res->end == 0xCFF;
}