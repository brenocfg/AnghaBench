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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct komeda_format_caps_table {int (* format_mod_supported ) (struct komeda_format_caps const*,int,int /*<<< orphan*/ ,int) ;} ;
struct komeda_format_caps {int supported_layer_types; } ;

/* Variables and functions */
 struct komeda_format_caps* komeda_get_format_caps (struct komeda_format_caps_table*,int,int /*<<< orphan*/ ) ; 
 int stub1 (struct komeda_format_caps const*,int,int /*<<< orphan*/ ,int) ; 

bool komeda_format_mod_supported(struct komeda_format_caps_table *table,
				 u32 layer_type, u32 fourcc, u64 modifier,
				 u32 rot)
{
	const struct komeda_format_caps *caps;

	caps = komeda_get_format_caps(table, fourcc, modifier);
	if (!caps)
		return false;

	if (!(caps->supported_layer_types & layer_type))
		return false;

	if (table->format_mod_supported)
		return table->format_mod_supported(caps, layer_type, modifier,
						   rot);

	return true;
}