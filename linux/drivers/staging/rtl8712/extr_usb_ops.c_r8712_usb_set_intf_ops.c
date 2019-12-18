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
struct _io_ops {int /*<<< orphan*/  _write_port; int /*<<< orphan*/  _write_mem; int /*<<< orphan*/  _write32; int /*<<< orphan*/  _write16; int /*<<< orphan*/  _write8; int /*<<< orphan*/  _read_port; int /*<<< orphan*/  _read32; int /*<<< orphan*/  _read16; int /*<<< orphan*/  _read8; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  r8712_usb_read_port ; 
 int /*<<< orphan*/  r8712_usb_write_mem ; 
 int /*<<< orphan*/  r8712_usb_write_port ; 
 int /*<<< orphan*/  usb_read16 ; 
 int /*<<< orphan*/  usb_read32 ; 
 int /*<<< orphan*/  usb_read8 ; 
 int /*<<< orphan*/  usb_write16 ; 
 int /*<<< orphan*/  usb_write32 ; 
 int /*<<< orphan*/  usb_write8 ; 

void r8712_usb_set_intf_ops(struct _io_ops *ops)
{
	memset((u8 *)ops, 0, sizeof(struct _io_ops));
	ops->_read8 = usb_read8;
	ops->_read16 = usb_read16;
	ops->_read32 = usb_read32;
	ops->_read_port = r8712_usb_read_port;
	ops->_write8 = usb_write8;
	ops->_write16 = usb_write16;
	ops->_write32 = usb_write32;
	ops->_write_mem = r8712_usb_write_mem;
	ops->_write_port = r8712_usb_write_port;
}