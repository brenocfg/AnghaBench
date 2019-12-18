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
struct fdc_word {int word; int bytes; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */

__attribute__((used)) static struct fdc_word mips_ejtag_fdc_encode(const char **ptrs,
					     unsigned int *sizes,
					     unsigned int ranges)
{
	struct fdc_word word = { 0, 0 };
	const char **ptrs_end = ptrs + ranges;

	for (; ptrs < ptrs_end; ++ptrs) {
		const char *ptr = *(ptrs++);
		const char *end = ptr + *(sizes++);

		for (; ptr < end; ++ptr) {
			word.word |= (u8)*ptr << (8*word.bytes);
			++word.bytes;
			if (word.bytes == 4)
				goto done;
		}
	}
done:
	/* Choose the appropriate encoding */
	switch (word.bytes) {
	case 4:
		/* 4 byte encoding, but don't match the 1-3 byte encodings */
		if ((word.word >> 8) != 0x808080 &&
		    (word.word >> 16) != 0x8181 &&
		    (word.word >> 24) != 0x82)
			break;
		/* Fall back to a 3 byte encoding */
		word.bytes = 3;
		word.word &= 0x00ffffff;
	case 3:
		/* 3 byte encoding */
		word.word |= 0x82000000;
		break;
	case 2:
		/* 2 byte encoding */
		word.word |= 0x81810000;
		break;
	case 1:
		/* 1 byte encoding */
		word.word |= 0x80808000;
		break;
	}
	return word;
}