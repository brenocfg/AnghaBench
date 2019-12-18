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
struct efx_filter_spec {int match_flags; int encap_type; } ;
typedef  enum efx_encap_type { ____Placeholder_efx_encap_type } efx_encap_type ;

/* Variables and functions */
 int EFX_ENCAP_TYPE_NONE ; 
 int EFX_FILTER_MATCH_ENCAP_TYPE ; 

__attribute__((used)) static inline enum efx_encap_type efx_filter_get_encap_type(
		const struct efx_filter_spec *spec)
{
	if (spec->match_flags & EFX_FILTER_MATCH_ENCAP_TYPE)
		return spec->encap_type;
	return EFX_ENCAP_TYPE_NONE;
}