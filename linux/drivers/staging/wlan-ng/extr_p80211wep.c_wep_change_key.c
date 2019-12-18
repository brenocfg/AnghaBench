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
struct wlandevice {int* wep_keylens; int /*<<< orphan*/ * wep_keys; } ;

/* Variables and functions */
 int MAX_KEYLEN ; 
 int NUM_WEPKEYS ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int wep_change_key(struct wlandevice *wlandev, int keynum, u8 *key, int keylen)
{
	if (keylen < 0)
		return -1;
	if (keylen >= MAX_KEYLEN)
		return -1;
	if (!key)
		return -1;
	if (keynum < 0)
		return -1;
	if (keynum >= NUM_WEPKEYS)
		return -1;

	wlandev->wep_keylens[keynum] = keylen;
	memcpy(wlandev->wep_keys[keynum], key, keylen);

	return 0;
}