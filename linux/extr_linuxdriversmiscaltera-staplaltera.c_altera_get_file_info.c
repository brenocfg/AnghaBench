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
typedef  int u32 ;
typedef  long s32 ;

/* Variables and functions */
 int EIO ; 
 int get_unaligned_be32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int altera_get_file_info(u8 *p,
					s32 program_size,
					int *format_version,
					int *action_count,
					int *procedure_count)
{
	int status = -EIO;
	u32 first_word = 0;
	int version = 0;

	if (program_size <= 52L)
		return status;

	first_word = get_unaligned_be32(&p[0]);

	if ((first_word == 0x4A414D00L) || (first_word == 0x4A414D01L)) {
		status = 0;

		version = (first_word & 1L);
		*format_version = version + 1;

		if (version > 0) {
			*action_count = get_unaligned_be32(&p[48]);
			*procedure_count = get_unaligned_be32(&p[52]);
		}
	}

	return status;
}