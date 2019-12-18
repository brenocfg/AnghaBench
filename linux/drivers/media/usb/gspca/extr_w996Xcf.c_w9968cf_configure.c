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
struct sd {int stopped; } ;

/* Variables and functions */
 int /*<<< orphan*/  reg_w (struct sd*,int,int) ; 

__attribute__((used)) static void w9968cf_configure(struct sd *sd)
{
	reg_w(sd, 0x00, 0xff00); /* power-down */
	reg_w(sd, 0x00, 0xbf17); /* reset everything */
	reg_w(sd, 0x00, 0xbf10); /* normal operation */
	reg_w(sd, 0x01, 0x0010); /* serial bus, SDS high */
	reg_w(sd, 0x01, 0x0000); /* serial bus, SDS low */
	reg_w(sd, 0x01, 0x0010); /* ..high 'beep-beep' */
	reg_w(sd, 0x01, 0x0030); /* Set sda scl to FSB mode */

	sd->stopped = 1;
}