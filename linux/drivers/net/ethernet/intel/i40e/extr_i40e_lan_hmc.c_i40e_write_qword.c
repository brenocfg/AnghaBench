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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u64 ;
typedef  int u16 ;
struct i40e_context_ele {int offset; int lsb; int width; } ;
typedef  int /*<<< orphan*/  dest_qword ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int BIT_ULL (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void i40e_write_qword(u8 *hmc_bits,
			     struct i40e_context_ele *ce_info,
			     u8 *src)
{
	u64 src_qword, mask;
	u8 *from, *dest;
	u16 shift_width;
	__le64 dest_qword;

	/* copy from the next struct field */
	from = src + ce_info->offset;

	/* prepare the bits and mask */
	shift_width = ce_info->lsb % 8;

	/* if the field width is exactly 64 on an x86 machine, then the shift
	 * operation will not work because the SHL instructions count is masked
	 * to 6 bits so the shift will do nothing
	 */
	if (ce_info->width < 64)
		mask = BIT_ULL(ce_info->width) - 1;
	else
		mask = ~(u64)0;

	/* don't swizzle the bits until after the mask because the mask bits
	 * will be in a different bit position on big endian machines
	 */
	src_qword = *(u64 *)from;
	src_qword &= mask;

	/* shift to correct alignment */
	mask <<= shift_width;
	src_qword <<= shift_width;

	/* get the current bits from the target bit string */
	dest = hmc_bits + (ce_info->lsb / 8);

	memcpy(&dest_qword, dest, sizeof(dest_qword));

	dest_qword &= ~(cpu_to_le64(mask));	/* get the bits not changing */
	dest_qword |= cpu_to_le64(src_qword);	/* add in the new bits */

	/* put it all back */
	memcpy(dest, &dest_qword, sizeof(dest_qword));
}