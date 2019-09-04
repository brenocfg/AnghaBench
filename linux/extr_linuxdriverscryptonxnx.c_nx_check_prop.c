#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u32 ;
struct device {int dummy; } ;
struct alg_props {scalar_t__ databytelen; int /*<<< orphan*/  sglen; } ;
struct TYPE_3__ {struct alg_props*** ap; } ;
struct TYPE_4__ {TYPE_1__ of; } ;

/* Variables and functions */
 scalar_t__ NX_PAGE_SIZE ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,size_t,size_t,int,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__ nx_driver ; 

__attribute__((used)) static bool nx_check_prop(struct device *dev, u32 fc, u32 mode, int slot)
{
	struct alg_props *props = &nx_driver.of.ap[fc][mode][slot];

	if (!props->sglen || props->databytelen < NX_PAGE_SIZE) {
		if (dev)
			dev_warn(dev, "bogus sglen/databytelen for %u/%u/%u: "
				 "%u/%u (ignored)\n", fc, mode, slot,
				 props->sglen, props->databytelen);
		return false;
	}

	return true;
}