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
typedef  scalar_t__ u8 ;
struct pci_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXCH ; 
 int /*<<< orphan*/  MAXDIMMPERCH ; 
 int /*<<< orphan*/  pci_read_config_byte (struct pci_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static void i5000_get_dimm_and_channel_counts(struct pci_dev *pdev,
					int *num_dimms_per_channel,
					int *num_channels)
{
	u8 value;

	/* Need to retrieve just how many channels and dimms per channel are
	 * supported on this memory controller
	 */
	pci_read_config_byte(pdev, MAXDIMMPERCH, &value);
	*num_dimms_per_channel = (int)value;

	pci_read_config_byte(pdev, MAXCH, &value);
	*num_channels = (int)value;
}