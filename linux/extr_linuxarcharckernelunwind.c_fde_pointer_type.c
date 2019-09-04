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
typedef  int uleb128_t ;
typedef  char u8 ;
typedef  int u32 ;

/* Variables and functions */
 int DW_EH_PE_abs ; 
 int DW_EH_PE_native ; 
 int /*<<< orphan*/  get_sleb128 (char const**,char const*) ; 
 int get_uleb128 (char const**,char const*) ; 
 char* memchr (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_pointer (char const**,char const*,int) ; 

__attribute__((used)) static signed fde_pointer_type(const u32 *cie)
{
	const u8 *ptr = (const u8 *)(cie + 2);
	unsigned version = *ptr;

	if (*++ptr) {
		const char *aug;
		const u8 *end = (const u8 *)(cie + 1) + *cie;
		uleb128_t len;

		/* check if augmentation size is first (and thus present) */
		if (*ptr != 'z')
			return -1;

		/* check if augmentation string is nul-terminated */
		aug = (const void *)ptr;
		ptr = memchr(aug, 0, end - ptr);
		if (ptr == NULL)
			return -1;

		++ptr;		/* skip terminator */
		get_uleb128(&ptr, end);	/* skip code alignment */
		get_sleb128(&ptr, end);	/* skip data alignment */
		/* skip return address column */
		version <= 1 ? (void) ++ptr : (void)get_uleb128(&ptr, end);
		len = get_uleb128(&ptr, end);	/* augmentation length */

		if (ptr + len < ptr || ptr + len > end)
			return -1;

		end = ptr + len;
		while (*++aug) {
			if (ptr >= end)
				return -1;
			switch (*aug) {
			case 'L':
				++ptr;
				break;
			case 'P':{
					signed ptrType = *ptr++;

					if (!read_pointer(&ptr, end, ptrType)
					    || ptr > end)
						return -1;
				}
				break;
			case 'R':
				return *ptr;
			default:
				return -1;
			}
		}
	}
	return DW_EH_PE_native | DW_EH_PE_abs;
}