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
typedef  int s32 ;

/* Variables and functions */
 int HEX_LINE_BITS ; 
 int HEX_LINE_CHARS ; 
 int /*<<< orphan*/  dprintk (char*,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void altera_export_bool_array(char *key, u8 *data, s32 count)
{
	char string[HEX_LINE_CHARS + 1];
	s32 i, offset;
	u32 size, line, lines, linebits, value, j, k;

	if (count > HEX_LINE_BITS) {
		dprintk("Export: key = \"%s\", %d bits, value = HEX\n",
							key, count);
		lines = (count + (HEX_LINE_BITS - 1)) / HEX_LINE_BITS;

		for (line = 0; line < lines; ++line) {
			if (line < (lines - 1)) {
				linebits = HEX_LINE_BITS;
				size = HEX_LINE_CHARS;
				offset = count - ((line + 1) * HEX_LINE_BITS);
			} else {
				linebits =
					count - ((lines - 1) * HEX_LINE_BITS);
				size = (linebits + 3) / 4;
				offset = 0L;
			}

			string[size] = '\0';
			j = size - 1;
			value = 0;

			for (k = 0; k < linebits; ++k) {
				i = k + offset;
				if (data[i >> 3] & (1 << (i & 7)))
					value |= (1 << (i & 3));
				if ((i & 3) == 3) {
					sprintf(&string[j], "%1x", value);
					value = 0;
					--j;
				}
			}
			if ((k & 3) > 0)
				sprintf(&string[j], "%1x", value);

			dprintk("%s\n", string);
		}

	} else {
		size = (count + 3) / 4;
		string[size] = '\0';
		j = size - 1;
		value = 0;

		for (i = 0; i < count; ++i) {
			if (data[i >> 3] & (1 << (i & 7)))
				value |= (1 << (i & 3));
			if ((i & 3) == 3) {
				sprintf(&string[j], "%1x", value);
				value = 0;
				--j;
			}
		}
		if ((i & 3) > 0)
			sprintf(&string[j], "%1x", value);

		dprintk("Export: key = \"%s\", %d bits, value = HEX %s\n",
			key, count, string);
	}
}