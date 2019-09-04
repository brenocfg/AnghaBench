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
struct zatm_dev {int dummy; } ;

/* Variables and functions */
 int ZEPROM_CS ; 
 int ZEPROM_DO ; 
 int ZEPROM_SK ; 
 int eprom_get (struct zatm_dev*,unsigned short) ; 
 int /*<<< orphan*/  eprom_set (struct zatm_dev*,int,unsigned short) ; 

__attribute__((used)) static void eprom_get_byte(struct zatm_dev *zatm_dev, unsigned char *byte,
			   unsigned short cmd)
{
	int i;

	*byte = 0;
	for (i = 8; i; i--) {
		eprom_set(zatm_dev,ZEPROM_CS,cmd);
		eprom_set(zatm_dev,ZEPROM_CS | ZEPROM_SK,cmd);
		*byte <<= 1;
		if (eprom_get(zatm_dev,cmd) & ZEPROM_DO) *byte |= 1;
		eprom_set(zatm_dev,ZEPROM_CS,cmd);
	}
}