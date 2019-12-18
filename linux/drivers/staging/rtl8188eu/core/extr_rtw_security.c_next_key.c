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

/* Variables and functions */
 int sbox (int) ; 
 int /*<<< orphan*/  xor_32 (int*,int*,int*) ; 

__attribute__((used)) static void next_key(u8 *key, int round)
{
	u8 rcon;
	u8 sbox_key[4];
	u8 rcon_table[12] = {
		0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80,
		0x1b, 0x36, 0x36, 0x36
	};

	sbox_key[0] = sbox(key[13]);
	sbox_key[1] = sbox(key[14]);
	sbox_key[2] = sbox(key[15]);
	sbox_key[3] = sbox(key[12]);

	rcon = rcon_table[round];

	xor_32(&key[0], sbox_key, &key[0]);
	key[0] = key[0] ^ rcon;

	xor_32(&key[4], &key[0], &key[4]);
	xor_32(&key[8], &key[4], &key[8]);
	xor_32(&key[12], &key[8], &key[12]);
}