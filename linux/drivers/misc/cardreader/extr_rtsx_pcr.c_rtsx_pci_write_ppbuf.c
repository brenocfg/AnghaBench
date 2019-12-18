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
typedef  int /*<<< orphan*/  u16 ;
struct rtsx_pcr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PPBUF_BASE2 ; 
 int /*<<< orphan*/  WRITE_REG_CMD ; 
 int /*<<< orphan*/  rtsx_pci_add_cmd (struct rtsx_pcr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtsx_pci_init_cmd (struct rtsx_pcr*) ; 
 int rtsx_pci_send_cmd (struct rtsx_pcr*,int) ; 

int rtsx_pci_write_ppbuf(struct rtsx_pcr *pcr, u8 *buf, int buf_len)
{
	int err;
	int i, j;
	u16 reg;
	u8 *ptr;

	if (buf_len > 512)
		buf_len = 512;

	ptr = buf;
	reg = PPBUF_BASE2;
	for (i = 0; i < buf_len / 256; i++) {
		rtsx_pci_init_cmd(pcr);

		for (j = 0; j < 256; j++) {
			rtsx_pci_add_cmd(pcr, WRITE_REG_CMD,
					reg++, 0xFF, *ptr);
			ptr++;
		}

		err = rtsx_pci_send_cmd(pcr, 250);
		if (err < 0)
			return err;
	}

	if (buf_len % 256) {
		rtsx_pci_init_cmd(pcr);

		for (j = 0; j < buf_len % 256; j++) {
			rtsx_pci_add_cmd(pcr, WRITE_REG_CMD,
					reg++, 0xFF, *ptr);
			ptr++;
		}

		err = rtsx_pci_send_cmd(pcr, 250);
		if (err < 0)
			return err;
	}

	return 0;
}