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
struct sense_data {int dummy; } ;

/* Variables and functions */
 int ILLEGAL_REQUEST ; 
 int SENCODE_INVALID_CDB_FIELD ; 

__attribute__((used)) static inline void set_sense(struct sense_data *sense_data, u8 sense_key,
	u8 sense_code, u8 a_sense_code, u8 bit_pointer, u16 field_pointer)
{
	u8 *sense_buf = (u8 *)sense_data;
	/* Sense data valid, err code 70h */
	sense_buf[0] = 0x70; /* No info field */
	sense_buf[1] = 0;	/* Segment number, always zero */

	sense_buf[2] = sense_key;	/* Sense key */

	sense_buf[12] = sense_code;	/* Additional sense code */
	sense_buf[13] = a_sense_code;	/* Additional sense code qualifier */

	if (sense_key == ILLEGAL_REQUEST) {
		sense_buf[7] = 10;	/* Additional sense length */

		sense_buf[15] = bit_pointer;
		/* Illegal parameter is in the parameter block */
		if (sense_code == SENCODE_INVALID_CDB_FIELD)
			sense_buf[15] |= 0xc0;/* Std sense key specific field */
		/* Illegal parameter is in the CDB block */
		sense_buf[16] = field_pointer >> 8;	/* MSB */
		sense_buf[17] = field_pointer;		/* LSB */
	} else
		sense_buf[7] = 6;	/* Additional sense length */
}