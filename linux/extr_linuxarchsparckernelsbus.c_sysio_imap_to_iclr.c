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
 unsigned long SYSIO_ICLR_UNUSED0 ; 
 unsigned long SYSIO_IMAP_SLOT0 ; 

__attribute__((used)) static unsigned long sysio_imap_to_iclr(unsigned long imap)
{
	unsigned long diff = SYSIO_ICLR_UNUSED0 - SYSIO_IMAP_SLOT0;
	return imap + diff;
}