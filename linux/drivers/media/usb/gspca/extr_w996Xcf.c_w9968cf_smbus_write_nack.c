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
struct sd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  w9968cf_write_sb (struct sd*,int) ; 

__attribute__((used)) static void w9968cf_smbus_write_nack(struct sd *sd)
{
	/* No need to ensure SDA is high as we are always called after
	   read_byte which ends with SDA high */
	w9968cf_write_sb(sd, 0x0013); /* SDE=1, SDA=1, SCL=1 */
	w9968cf_write_sb(sd, 0x0012); /* SDE=1, SDA=1, SCL=0 */
}