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
typedef  int u32 ;

/* Variables and functions */
#define  INTEL_GUC_CT_BUFFER_TYPE_RECV 129 
#define  INTEL_GUC_CT_BUFFER_TYPE_SEND 128 

__attribute__((used)) static inline const char *guc_ct_buffer_type_to_str(u32 type)
{
	switch (type) {
	case INTEL_GUC_CT_BUFFER_TYPE_SEND:
		return "SEND";
	case INTEL_GUC_CT_BUFFER_TYPE_RECV:
		return "RECV";
	default:
		return "<invalid>";
	}
}