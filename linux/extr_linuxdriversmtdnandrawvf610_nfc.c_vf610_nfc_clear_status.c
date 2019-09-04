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
typedef  int u32 ;
struct vf610_nfc {int dummy; } ;

/* Variables and functions */
 int CMD_DONE_CLEAR_BIT ; 
 int IDLE_CLEAR_BIT ; 
 int /*<<< orphan*/  NFC_IRQ_STATUS ; 
 int vf610_nfc_read (struct vf610_nfc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vf610_nfc_write (struct vf610_nfc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void vf610_nfc_clear_status(struct vf610_nfc *nfc)
{
	u32 tmp = vf610_nfc_read(nfc, NFC_IRQ_STATUS);

	tmp |= CMD_DONE_CLEAR_BIT | IDLE_CLEAR_BIT;
	vf610_nfc_write(nfc, NFC_IRQ_STATUS, tmp);
}