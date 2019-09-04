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

/* Variables and functions */

__attribute__((used)) static void ace_fix_driveid(u16 *id)
{
#if defined(__BIG_ENDIAN)
	int i;

	/* All half words have wrong byte order; swap the bytes */
	for (i = 0; i < ATA_ID_WORDS; i++, id++)
		*id = le16_to_cpu(*id);
#endif
}