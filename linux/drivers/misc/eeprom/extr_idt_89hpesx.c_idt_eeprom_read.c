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
struct idt_89hpesx_dev {int /*<<< orphan*/  smb_mtx; } ;

/* Variables and functions */
 int idt_eeprom_read_byte (struct idt_89hpesx_dev*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int idt_eeprom_read(struct idt_89hpesx_dev *pdev, u16 memaddr, u16 len,
			   u8 *buf)
{
	int ret;
	u16 idx;

	/* Read data byte-by-byte, retrying if it wasn't successful */
	for (idx = 0; idx < len; idx++, memaddr++) {
		/* Lock IDT SMBus device */
		mutex_lock(&pdev->smb_mtx);

		/* Just read the byte to the buffer */
		ret = idt_eeprom_read_byte(pdev, memaddr, &buf[idx]);

		/* Unlock IDT SMBus device */
		mutex_unlock(&pdev->smb_mtx);

		/* Return error if read operation failed */
		if (ret != 0)
			return ret;
	}

	return 0;
}