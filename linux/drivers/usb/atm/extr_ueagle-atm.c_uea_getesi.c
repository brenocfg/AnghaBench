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
typedef  int u_char ;
struct uea_softc {TYPE_2__* usb_dev; } ;
typedef  int /*<<< orphan*/  mac_str ;
struct TYPE_3__ {int /*<<< orphan*/  iSerialNumber; } ;
struct TYPE_4__ {TYPE_1__ descriptor; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int hex_to_bin (unsigned char) ; 
 int usb_string (TYPE_2__*,int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int uea_getesi(struct uea_softc *sc, u_char *esi)
{
	unsigned char mac_str[2 * ETH_ALEN + 1];
	int i;
	if (usb_string
	    (sc->usb_dev, sc->usb_dev->descriptor.iSerialNumber, mac_str,
	     sizeof(mac_str)) != 2 * ETH_ALEN)
		return 1;

	for (i = 0; i < ETH_ALEN; i++)
		esi[i] = hex_to_bin(mac_str[2 * i]) * 16 +
			 hex_to_bin(mac_str[2 * i + 1]);

	return 0;
}