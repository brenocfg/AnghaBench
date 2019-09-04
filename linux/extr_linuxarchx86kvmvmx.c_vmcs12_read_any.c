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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct vmcs12 {int dummy; } ;
typedef  int /*<<< orphan*/  natural_width ;

/* Variables and functions */
 int ENOENT ; 
#define  VMCS_FIELD_WIDTH_NATURAL_WIDTH 131 
#define  VMCS_FIELD_WIDTH_U16 130 
#define  VMCS_FIELD_WIDTH_U32 129 
#define  VMCS_FIELD_WIDTH_U64 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 short vmcs_field_to_offset (unsigned long) ; 
 int vmcs_field_width (unsigned long) ; 

__attribute__((used)) static inline int vmcs12_read_any(struct vmcs12 *vmcs12,
				  unsigned long field, u64 *ret)
{
	short offset = vmcs_field_to_offset(field);
	char *p;

	if (offset < 0)
		return offset;

	p = (char *)vmcs12 + offset;

	switch (vmcs_field_width(field)) {
	case VMCS_FIELD_WIDTH_NATURAL_WIDTH:
		*ret = *((natural_width *)p);
		return 0;
	case VMCS_FIELD_WIDTH_U16:
		*ret = *((u16 *)p);
		return 0;
	case VMCS_FIELD_WIDTH_U32:
		*ret = *((u32 *)p);
		return 0;
	case VMCS_FIELD_WIDTH_U64:
		*ret = *((u64 *)p);
		return 0;
	default:
		WARN_ON(1);
		return -ENOENT;
	}
}