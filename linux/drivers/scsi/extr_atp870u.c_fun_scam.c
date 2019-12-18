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
struct atp_unit {int dummy; } ;

/* Variables and functions */
 int atp_readw_io (struct atp_unit*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atp_writew_io (struct atp_unit*,int /*<<< orphan*/ ,int,unsigned short) ; 

__attribute__((used)) static unsigned char fun_scam(struct atp_unit *dev, unsigned short int *val)
{
	unsigned short int i, k;
	unsigned char j;

	atp_writew_io(dev, 0, 0x1c, *val);
	for (i = 0; i < 10; i++) {	/* stable >= bus settle delay(400 ns)  */
		k = atp_readw_io(dev, 0, 0x1c);
		j = (unsigned char) (k >> 8);
		if ((k & 0x8000) != 0)	/* DB7 all release?    */
			i = 0;
	}
	*val |= 0x4000;		/* assert DB6           */
	atp_writew_io(dev, 0, 0x1c, *val);
	*val &= 0xdfff;		/* assert DB5           */
	atp_writew_io(dev, 0, 0x1c, *val);
	for (i = 0; i < 10; i++) {	/* stable >= bus settle delay(400 ns) */
		if ((atp_readw_io(dev, 0, 0x1c) & 0x2000) != 0)	/* DB5 all release?       */
			i = 0;
	}
	*val |= 0x8000;		/* no DB4-0, assert DB7    */
	*val &= 0xe0ff;
	atp_writew_io(dev, 0, 0x1c, *val);
	*val &= 0xbfff;		/* release DB6             */
	atp_writew_io(dev, 0, 0x1c, *val);
	for (i = 0; i < 10; i++) {	/* stable >= bus settle delay(400 ns)  */
		if ((atp_readw_io(dev, 0, 0x1c) & 0x4000) != 0)	/* DB6 all release?  */
			i = 0;
	}

	return j;
}