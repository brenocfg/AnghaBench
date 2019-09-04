#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned char* BootBuf; } ;
struct boot_data {int Cryptor; TYPE_1__ buf; } ;

/* Variables and functions */
 int CRYPT_FEEDTERM ; 

__attribute__((used)) static void
DecryptBuf(struct boot_data *boot, int cnt)
{
	unsigned char *bufp = boot->buf.BootBuf;

	while (cnt--) {
		boot->Cryptor = (boot->Cryptor >> 1) ^ ((boot->Cryptor & 1U) ? CRYPT_FEEDTERM : 0);
		*bufp++ ^= (unsigned char)boot->Cryptor;
	}
}