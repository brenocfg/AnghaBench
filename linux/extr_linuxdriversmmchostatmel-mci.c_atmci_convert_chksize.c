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
struct atmel_mci {int dummy; } ;

/* Variables and functions */
 unsigned int atmci_get_version (struct atmel_mci*) ; 
 unsigned int fls (unsigned int) ; 

__attribute__((used)) static inline unsigned int atmci_convert_chksize(struct atmel_mci *host,
						 unsigned int maxburst)
{
	unsigned int version = atmci_get_version(host);
	unsigned int offset = 2;

	if (version >= 0x600)
		offset = 1;

	if (maxburst > 1)
		return fls(maxburst) - offset;
	else
		return 0;
}