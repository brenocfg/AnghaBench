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
typedef  size_t u16 ;
struct isci_host {size_t* io_request_sequence; } ;
typedef  enum sci_status { ____Placeholder_sci_status } sci_status ;

/* Variables and functions */
 size_t ISCI_TAG_SEQ (size_t) ; 
 size_t ISCI_TAG_TCI (size_t) ; 
 int SCI_FAILURE_INVALID_IO_TAG ; 
 int SCI_MAX_SEQ ; 
 int SCI_SUCCESS ; 
 scalar_t__ isci_tci_active (struct isci_host*) ; 
 int /*<<< orphan*/  isci_tci_free (struct isci_host*,size_t) ; 

enum sci_status isci_free_tag(struct isci_host *ihost, u16 io_tag)
{
	u16 tci = ISCI_TAG_TCI(io_tag);
	u16 seq = ISCI_TAG_SEQ(io_tag);

	/* prevent tail from passing head */
	if (isci_tci_active(ihost) == 0)
		return SCI_FAILURE_INVALID_IO_TAG;

	if (seq == ihost->io_request_sequence[tci]) {
		ihost->io_request_sequence[tci] = (seq+1) & (SCI_MAX_SEQ-1);

		isci_tci_free(ihost, tci);

		return SCI_SUCCESS;
	}
	return SCI_FAILURE_INVALID_IO_TAG;
}