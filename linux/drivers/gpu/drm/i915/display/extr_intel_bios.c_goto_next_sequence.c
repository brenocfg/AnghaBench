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
typedef  int u16 ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
#define  MIPI_SEQ_ELEM_DELAY 132 
#define  MIPI_SEQ_ELEM_END 131 
#define  MIPI_SEQ_ELEM_GPIO 130 
#define  MIPI_SEQ_ELEM_I2C 129 
#define  MIPI_SEQ_ELEM_SEND_PKT 128 

__attribute__((used)) static int goto_next_sequence(const u8 *data, int index, int total)
{
	u16 len;

	/* Skip Sequence Byte. */
	for (index = index + 1; index < total; index += len) {
		u8 operation_byte = *(data + index);
		index++;

		switch (operation_byte) {
		case MIPI_SEQ_ELEM_END:
			return index;
		case MIPI_SEQ_ELEM_SEND_PKT:
			if (index + 4 > total)
				return 0;

			len = *((const u16 *)(data + index + 2)) + 4;
			break;
		case MIPI_SEQ_ELEM_DELAY:
			len = 4;
			break;
		case MIPI_SEQ_ELEM_GPIO:
			len = 2;
			break;
		case MIPI_SEQ_ELEM_I2C:
			if (index + 7 > total)
				return 0;
			len = *(data + index + 6) + 7;
			break;
		default:
			DRM_ERROR("Unknown operation byte\n");
			return 0;
		}
	}

	return 0;
}