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
typedef  int /*<<< orphan*/  u8 ;
typedef  size_t u16 ;
struct isci_host {int /*<<< orphan*/ * io_request_sequence; } ;

/* Variables and functions */
 size_t ISCI_TAG (int /*<<< orphan*/ ,size_t) ; 
 size_t SCI_CONTROLLER_INVALID_IO_TAG ; 
 size_t isci_tci_alloc (struct isci_host*) ; 
 scalar_t__ isci_tci_space (struct isci_host*) ; 

u16 isci_alloc_tag(struct isci_host *ihost)
{
	if (isci_tci_space(ihost)) {
		u16 tci = isci_tci_alloc(ihost);
		u8 seq = ihost->io_request_sequence[tci];

		return ISCI_TAG(seq, tci);
	}

	return SCI_CONTROLLER_INVALID_IO_TAG;
}