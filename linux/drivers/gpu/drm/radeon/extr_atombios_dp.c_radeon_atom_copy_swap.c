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
typedef  int u8 ;
typedef  int u32 ;

/* Variables and functions */
 int ALIGN (int,int) ; 
 int cpu_to_le32 (int) ; 
 int le32_to_cpu (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

void radeon_atom_copy_swap(u8 *dst, u8 *src, u8 num_bytes, bool to_le)
{
#ifdef __BIG_ENDIAN
	u32 src_tmp[5], dst_tmp[5];
	int i;
	u8 align_num_bytes = ALIGN(num_bytes, 4);

	if (to_le) {
		memcpy(src_tmp, src, num_bytes);
		for (i = 0; i < align_num_bytes / 4; i++)
			dst_tmp[i] = cpu_to_le32(src_tmp[i]);
		memcpy(dst, dst_tmp, align_num_bytes);
	} else {
		memcpy(src_tmp, src, align_num_bytes);
		for (i = 0; i < align_num_bytes / 4; i++)
			dst_tmp[i] = le32_to_cpu(src_tmp[i]);
		memcpy(dst, dst_tmp, num_bytes);
	}
#else
	memcpy(dst, src, num_bytes);
#endif
}