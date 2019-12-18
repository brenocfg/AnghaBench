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
struct _adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  r8712_fw_cmd (struct _adapter*,int) ; 

__attribute__((used)) static void enable_video_mode(struct _adapter *padapter, int cbw40_value)
{
	/*   bit 8:
	 *   1 -> enable video mode to 96B AP
	 *   0 -> disable video mode to 96B AP
	 *   bit 9:
	 *   1 -> enable 40MHz mode
	 *   0 -> disable 40MHz mode
	 *   bit 10:
	 *   1 -> enable STBC
	 *   0 -> disable STBC
	 */
	u32  intcmd = 0xf4000500;   /* enable bit8, bit10*/

	if (cbw40_value) {
		/* if the driver supports the 40M bandwidth,
		 * we can enable the bit 9.
		 */
		intcmd |= 0x200;
	}
	r8712_fw_cmd(padapter, intcmd);
}