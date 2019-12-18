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
struct ssb_sprom {int dummy; } ;
struct ssb_bus {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int get_fallback_sprom (struct ssb_bus*,struct ssb_sprom*) ; 

int ssb_fill_sprom_with_fallback(struct ssb_bus *bus, struct ssb_sprom *out)
{
	if (!get_fallback_sprom)
		return -ENOENT;

	return get_fallback_sprom(bus, out);
}