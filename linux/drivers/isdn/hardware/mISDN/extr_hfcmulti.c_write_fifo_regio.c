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
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct hfc_multi {scalar_t__ pci_iobase; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_FIFO_DATA0 ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outl (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  outw (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
write_fifo_regio(struct hfc_multi *hc, u_char *data, int len)
{
	outb(A_FIFO_DATA0, (hc->pci_iobase) + 4);
	while (len >> 2) {
		outl(cpu_to_le32(*(u32 *)data), hc->pci_iobase);
		data += 4;
		len -= 4;
	}
	while (len >> 1) {
		outw(cpu_to_le16(*(u16 *)data), hc->pci_iobase);
		data += 2;
		len -= 2;
	}
	while (len) {
		outb(*data, hc->pci_iobase);
		data++;
		len--;
	}
}