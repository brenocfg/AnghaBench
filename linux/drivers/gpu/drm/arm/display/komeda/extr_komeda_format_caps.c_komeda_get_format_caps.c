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
typedef  unsigned long long u64 ;
typedef  scalar_t__ u32 ;
struct komeda_format_caps_table {int n_formats; struct komeda_format_caps* format_caps; } ;
struct komeda_format_caps {scalar_t__ fourcc; scalar_t__ supported_afbc_layouts; int /*<<< orphan*/  supported_afbc_features; } ;

/* Variables and functions */
 unsigned long long AFBC_FORMAT_MOD_BLOCK_SIZE_MASK ; 
 scalar_t__ has_bit (scalar_t__,scalar_t__) ; 
 scalar_t__ has_bits (unsigned long long,int /*<<< orphan*/ ) ; 

const struct komeda_format_caps *
komeda_get_format_caps(struct komeda_format_caps_table *table,
		       u32 fourcc, u64 modifier)
{
	const struct komeda_format_caps *caps;
	u64 afbc_features = modifier & ~(AFBC_FORMAT_MOD_BLOCK_SIZE_MASK);
	u32 afbc_layout = modifier & AFBC_FORMAT_MOD_BLOCK_SIZE_MASK;
	int id;

	for (id = 0; id < table->n_formats; id++) {
		caps = &table->format_caps[id];

		if (fourcc != caps->fourcc)
			continue;

		if ((modifier == 0ULL) && (caps->supported_afbc_layouts == 0))
			return caps;

		if (has_bits(afbc_features, caps->supported_afbc_features) &&
		    has_bit(afbc_layout, caps->supported_afbc_layouts))
			return caps;
	}

	return NULL;
}