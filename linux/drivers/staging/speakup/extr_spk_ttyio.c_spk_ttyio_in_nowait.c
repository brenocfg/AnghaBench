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

/* Variables and functions */
 int ttyio_in (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned char spk_ttyio_in_nowait(void)
{
	u8 rv = ttyio_in(0);

	return (rv == 0xff) ? 0 : rv;
}