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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int uint16_t ;
struct pp_hwmgr {int dummy; } ;

/* Variables and functions */
 int ATOM_PPLIB_CLASSIFICATION2_LIMITEDPOWERSOURCE_2 ; 
 int ATOM_PPLIB_CLASSIFICATION_ACPI ; 
 int ATOM_PPLIB_CLASSIFICATION_BOOT ; 
 int ATOM_PPLIB_CLASSIFICATION_FORCED ; 
 int ATOM_PPLIB_CLASSIFICATION_LIMITEDPOWERSOURCE ; 
 int ATOM_PPLIB_CLASSIFICATION_REST ; 
 int ATOM_PPLIB_CLASSIFICATION_THERMAL ; 
 int /*<<< orphan*/  PP_StateClassificationFlag_ACPI ; 
 int /*<<< orphan*/  PP_StateClassificationFlag_Boot ; 
 int /*<<< orphan*/  PP_StateClassificationFlag_Forced ; 
 int /*<<< orphan*/  PP_StateClassificationFlag_LimitedPowerSource ; 
 int /*<<< orphan*/  PP_StateClassificationFlag_LimitedPowerSource_2 ; 
 int /*<<< orphan*/  PP_StateClassificationFlag_Rest ; 
 int /*<<< orphan*/  PP_StateClassificationFlag_Thermal ; 

__attribute__((used)) static uint32_t make_classification_flags(struct pp_hwmgr *hwmgr,
		uint16_t classification, uint16_t classification2)
{
	uint32_t result = 0;

	if (classification & ATOM_PPLIB_CLASSIFICATION_BOOT)
		result |= PP_StateClassificationFlag_Boot;

	if (classification & ATOM_PPLIB_CLASSIFICATION_THERMAL)
		result |= PP_StateClassificationFlag_Thermal;

	if (classification & ATOM_PPLIB_CLASSIFICATION_LIMITEDPOWERSOURCE)
		result |= PP_StateClassificationFlag_LimitedPowerSource;

	if (classification & ATOM_PPLIB_CLASSIFICATION_REST)
		result |= PP_StateClassificationFlag_Rest;

	if (classification & ATOM_PPLIB_CLASSIFICATION_FORCED)
		result |= PP_StateClassificationFlag_Forced;

	if (classification & ATOM_PPLIB_CLASSIFICATION_ACPI)
		result |= PP_StateClassificationFlag_ACPI;

	if (classification2 & ATOM_PPLIB_CLASSIFICATION2_LIMITEDPOWERSOURCE_2)
		result |= PP_StateClassificationFlag_LimitedPowerSource_2;

	return result;
}