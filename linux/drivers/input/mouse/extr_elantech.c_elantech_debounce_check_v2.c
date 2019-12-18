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
typedef  int u8 ;
struct psmouse {unsigned char* packet; } ;
typedef  int /*<<< orphan*/  debounce_packet ;

/* Variables and functions */
 int /*<<< orphan*/  memcmp (unsigned char*,int const*,int) ; 

__attribute__((used)) static int elantech_debounce_check_v2(struct psmouse *psmouse)
{
        /*
         * When we encounter packet that matches this exactly, it means the
         * hardware is in debounce status. Just ignore the whole packet.
         */
	static const u8 debounce_packet[] = {
		0x84, 0xff, 0xff, 0x02, 0xff, 0xff
	};
        unsigned char *packet = psmouse->packet;

        return !memcmp(packet, debounce_packet, sizeof(debounce_packet));
}