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

/* Variables and functions */
 unsigned int CQHCI_EXTERNAL_TIMEOUT ; 
 unsigned int CQHCI_HOST_CRC ; 
 unsigned int CQHCI_HOST_TIMEOUT ; 
 int EILSEQ ; 
 int EIO ; 
 int ETIMEDOUT ; 

__attribute__((used)) static int cqhci_error_from_flags(unsigned int flags)
{
	if (!flags)
		return 0;

	/* CRC errors might indicate re-tuning so prefer to report that */
	if (flags & CQHCI_HOST_CRC)
		return -EILSEQ;

	if (flags & (CQHCI_EXTERNAL_TIMEOUT | CQHCI_HOST_TIMEOUT))
		return -ETIMEDOUT;

	return -EIO;
}