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
typedef  int /*<<< orphan*/  u32 ;
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/ * of_get_property (struct device_node*,char const*,int*) ; 
 int /*<<< orphan*/  of_read_number (int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static u32 get_int_prop(struct device_node *np, const char *name, u32 def)
{
	const __be32 *prop;
	int len;

	prop = of_get_property(np, name, &len);
	if (prop && len >= 4)
		return of_read_number(prop, 1);
	return def;
}