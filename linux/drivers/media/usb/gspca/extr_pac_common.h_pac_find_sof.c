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
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_FRAM ; 
 int /*<<< orphan*/  gspca_dbg (struct gspca_dev*,int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static unsigned char *pac_find_sof(struct gspca_dev *gspca_dev, u8 *sof_read,
					unsigned char *m, int len)
{
	int i;

	/* Search for the SOF marker (fixed part) in the header */
	for (i = 0; i < len; i++) {
		switch (*sof_read) {
		case 0:
			if (m[i] == 0xff)
				*sof_read = 1;
			break;
		case 1:
			if (m[i] == 0xff)
				*sof_read = 2;
			else
				*sof_read = 0;
			break;
		case 2:
			switch (m[i]) {
			case 0x00:
				*sof_read = 3;
				break;
			case 0xff:
				/* stay in this state */
				break;
			default:
				*sof_read = 0;
			}
			break;
		case 3:
			if (m[i] == 0xff)
				*sof_read = 4;
			else
				*sof_read = 0;
			break;
		case 4:
			switch (m[i]) {
			case 0x96:
				/* Pattern found */
				gspca_dbg(gspca_dev, D_FRAM,
					  "SOF found, bytes to analyze: %u - Frame starts at byte #%u\n",
					  len, i + 1);
				*sof_read = 0;
				return m + i + 1;
				break;
			case 0xff:
				*sof_read = 2;
				break;
			default:
				*sof_read = 0;
			}
			break;
		default:
			*sof_read = 0;
		}
	}

	return NULL;
}