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

/* Variables and functions */
#define  ADB_PACKET 129 
 int /*<<< orphan*/  DUMP_PREFIX_NONE ; 
 int /*<<< orphan*/  KERN_INFO ; 
#define  TIMER_PACKET 128 
 int /*<<< orphan*/  adb_input (unsigned char*,int,unsigned char) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,unsigned char*,int,int) ; 

__attribute__((used)) static void
cuda_input(unsigned char *buf, int nb)
{
    switch (buf[0]) {
    case ADB_PACKET:
#ifdef CONFIG_XMON
	if (nb == 5 && buf[2] == 0x2c) {
	    extern int xmon_wants_key, xmon_adb_keycode;
	    if (xmon_wants_key) {
		xmon_adb_keycode = buf[3];
		return;
	    }
	}
#endif /* CONFIG_XMON */
#ifdef CONFIG_ADB
	adb_input(buf+2, nb-2, buf[1] & 0x40);
#endif /* CONFIG_ADB */
	break;

    case TIMER_PACKET:
	/* Egret sends these periodically. Might be useful as a 'heartbeat'
	 * to trigger a recovery for the VIA shift register errata.
	 */
	break;

    default:
	print_hex_dump(KERN_INFO, "cuda_input: ", DUMP_PREFIX_NONE, 32, 1,
	               buf, nb, false);
    }
}