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
struct resource {scalar_t__ desc; } ;

/* Variables and functions */
 scalar_t__ IORES_DESC_NONE ; 

__attribute__((used)) static int __ioremap_check_desc_other(struct resource *res)
{
	return (res->desc != IORES_DESC_NONE);
}