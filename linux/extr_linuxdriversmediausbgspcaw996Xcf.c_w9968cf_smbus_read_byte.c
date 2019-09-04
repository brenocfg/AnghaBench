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
struct sd {int dummy; } ;

/* Variables and functions */
 int w9968cf_read_sb (struct sd*) ; 
 int /*<<< orphan*/  w9968cf_write_sb (struct sd*,int) ; 

__attribute__((used)) static void w9968cf_smbus_read_byte(struct sd *sd, u8 *v)
{
	u8 bit;

	/* No need to ensure SDA is high as we are always called after
	   read_ack which ends with SDA high */
	*v = 0;
	for (bit = 0 ; bit < 8 ; bit++) {
		*v <<= 1;
		/* SDE=1, SDA=1, SCL=1 */
		w9968cf_write_sb(sd, 0x0013);
		*v |= (w9968cf_read_sb(sd) & 0x0008) ? 1 : 0;
		/* SDE=1, SDA=1, SCL=0 */
		w9968cf_write_sb(sd, 0x0012);
	}
}