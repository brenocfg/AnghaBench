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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  QCAFRM_FOOTER_LEN ; 

u16
qcafrm_create_footer(u8 *buf)
{
	if (!buf)
		return 0;

	buf[0] = 0x55;
	buf[1] = 0x55;
	return QCAFRM_FOOTER_LEN;
}