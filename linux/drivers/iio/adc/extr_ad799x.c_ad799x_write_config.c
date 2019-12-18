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
typedef  int /*<<< orphan*/  u16 ;
struct ad799x_state {int id; int /*<<< orphan*/  config; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7998_CONF_REG ; 
#define  ad7992 132 
#define  ad7993 131 
#define  ad7994 130 
#define  ad7997 129 
#define  ad7998 128 
 int i2c_smbus_write_byte_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i2c_smbus_write_word_swapped (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ad799x_write_config(struct ad799x_state *st, u16 val)
{
	switch (st->id) {
	case ad7997:
	case ad7998:
		return i2c_smbus_write_word_swapped(st->client, AD7998_CONF_REG,
			val);
	case ad7992:
	case ad7993:
	case ad7994:
		return i2c_smbus_write_byte_data(st->client, AD7998_CONF_REG,
			val);
	default:
		/* Will be written when doing a conversion */
		st->config = val;
		return 0;
	}
}