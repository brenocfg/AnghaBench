#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xilly_idt_handle {unsigned char* idt; unsigned char* chandesc; int entries; } ;
struct xilly_endpoint {int idtlen; int num_channels; int /*<<< orphan*/  dev; TYPE_2__** channels; } ;
struct TYPE_4__ {TYPE_1__** wr_buffers; } ;
struct TYPE_3__ {unsigned char* addr; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int xilly_scan_idt(struct xilly_endpoint *endpoint,
			  struct xilly_idt_handle *idt_handle)
{
	int count = 0;
	unsigned char *idt = endpoint->channels[1]->wr_buffers[0]->addr;
	unsigned char *end_of_idt = idt + endpoint->idtlen - 4;
	unsigned char *scan;
	int len;

	scan = idt;
	idt_handle->idt = idt;

	scan++; /* Skip version number */

	while ((scan <= end_of_idt) && *scan) {
		while ((scan <= end_of_idt) && *scan++)
			/* Do nothing, just scan thru string */;
		count++;
	}

	scan++;

	if (scan > end_of_idt) {
		dev_err(endpoint->dev,
			"IDT device name list overflow. Aborting.\n");
		return -ENODEV;
	}
	idt_handle->chandesc = scan;

	len = endpoint->idtlen - (3 + ((int) (scan - idt)));

	if (len & 0x03) {
		dev_err(endpoint->dev,
			"Corrupt IDT device name list. Aborting.\n");
		return -ENODEV;
	}

	idt_handle->entries = len >> 2;
	endpoint->num_channels = count;

	return 0;
}