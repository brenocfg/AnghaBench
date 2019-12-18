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
struct pci_dev {int broken_parity_status; } ;

/* Variables and functions */

__attribute__((used)) static void quirk_mellanox_tavor(struct pci_dev *dev)
{
	dev->broken_parity_status = 1;	/* This device gives false positives */
}