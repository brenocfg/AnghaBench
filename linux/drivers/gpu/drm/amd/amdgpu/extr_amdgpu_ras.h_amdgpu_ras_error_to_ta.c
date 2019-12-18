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
typedef  enum ta_ras_error_type { ____Placeholder_ta_ras_error_type } ta_ras_error_type ;
typedef  enum amdgpu_ras_error_type { ____Placeholder_amdgpu_ras_error_type } amdgpu_ras_error_type ;

/* Variables and functions */
#define  AMDGPU_RAS_ERROR__MULTI_UNCORRECTABLE 132 
#define  AMDGPU_RAS_ERROR__NONE 131 
#define  AMDGPU_RAS_ERROR__PARITY 130 
#define  AMDGPU_RAS_ERROR__POISON 129 
#define  AMDGPU_RAS_ERROR__SINGLE_CORRECTABLE 128 
 int TA_RAS_ERROR__MULTI_UNCORRECTABLE ; 
 int TA_RAS_ERROR__NONE ; 
 int TA_RAS_ERROR__PARITY ; 
 int TA_RAS_ERROR__POISON ; 
 int TA_RAS_ERROR__SINGLE_CORRECTABLE ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int) ; 

__attribute__((used)) static inline enum ta_ras_error_type
amdgpu_ras_error_to_ta(enum amdgpu_ras_error_type error) {
	switch (error) {
	case AMDGPU_RAS_ERROR__NONE:
		return TA_RAS_ERROR__NONE;
	case AMDGPU_RAS_ERROR__PARITY:
		return TA_RAS_ERROR__PARITY;
	case AMDGPU_RAS_ERROR__SINGLE_CORRECTABLE:
		return TA_RAS_ERROR__SINGLE_CORRECTABLE;
	case AMDGPU_RAS_ERROR__MULTI_UNCORRECTABLE:
		return TA_RAS_ERROR__MULTI_UNCORRECTABLE;
	case AMDGPU_RAS_ERROR__POISON:
		return TA_RAS_ERROR__POISON;
	default:
		WARN_ONCE(1, "RAS ERROR: unexpected error type %d\n", error);
		return TA_RAS_ERROR__NONE;
	}
}