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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  S0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_and_load_keys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  storekeys (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __serpent_setkey_sbox(u32 r0, u32 r1, u32 r2, u32 r3, u32 r4, u32 *k)
{
	k += 100;
	S3(r3, r4, r0, r1, r2); store_and_load_keys(r1, r2, r4, r3, 28, 24);
	S4(r1, r2, r4, r3, r0); store_and_load_keys(r2, r4, r3, r0, 24, 20);
	S5(r2, r4, r3, r0, r1); store_and_load_keys(r1, r2, r4, r0, 20, 16);
	S6(r1, r2, r4, r0, r3); store_and_load_keys(r4, r3, r2, r0, 16, 12);
	S7(r4, r3, r2, r0, r1); store_and_load_keys(r1, r2, r0, r4, 12, 8);
	S0(r1, r2, r0, r4, r3); store_and_load_keys(r0, r2, r4, r1, 8, 4);
	S1(r0, r2, r4, r1, r3); store_and_load_keys(r3, r4, r1, r0, 4, 0);
	S2(r3, r4, r1, r0, r2); store_and_load_keys(r2, r4, r3, r0, 0, -4);
	S3(r2, r4, r3, r0, r1); store_and_load_keys(r0, r1, r4, r2, -4, -8);
	S4(r0, r1, r4, r2, r3); store_and_load_keys(r1, r4, r2, r3, -8, -12);
	S5(r1, r4, r2, r3, r0); store_and_load_keys(r0, r1, r4, r3, -12, -16);
	S6(r0, r1, r4, r3, r2); store_and_load_keys(r4, r2, r1, r3, -16, -20);
	S7(r4, r2, r1, r3, r0); store_and_load_keys(r0, r1, r3, r4, -20, -24);
	S0(r0, r1, r3, r4, r2); store_and_load_keys(r3, r1, r4, r0, -24, -28);
	k -= 50;
	S1(r3, r1, r4, r0, r2); store_and_load_keys(r2, r4, r0, r3, 22, 18);
	S2(r2, r4, r0, r3, r1); store_and_load_keys(r1, r4, r2, r3, 18, 14);
	S3(r1, r4, r2, r3, r0); store_and_load_keys(r3, r0, r4, r1, 14, 10);
	S4(r3, r0, r4, r1, r2); store_and_load_keys(r0, r4, r1, r2, 10, 6);
	S5(r0, r4, r1, r2, r3); store_and_load_keys(r3, r0, r4, r2, 6, 2);
	S6(r3, r0, r4, r2, r1); store_and_load_keys(r4, r1, r0, r2, 2, -2);
	S7(r4, r1, r0, r2, r3); store_and_load_keys(r3, r0, r2, r4, -2, -6);
	S0(r3, r0, r2, r4, r1); store_and_load_keys(r2, r0, r4, r3, -6, -10);
	S1(r2, r0, r4, r3, r1); store_and_load_keys(r1, r4, r3, r2, -10, -14);
	S2(r1, r4, r3, r2, r0); store_and_load_keys(r0, r4, r1, r2, -14, -18);
	S3(r0, r4, r1, r2, r3); store_and_load_keys(r2, r3, r4, r0, -18, -22);
	k -= 50;
	S4(r2, r3, r4, r0, r1); store_and_load_keys(r3, r4, r0, r1, 28, 24);
	S5(r3, r4, r0, r1, r2); store_and_load_keys(r2, r3, r4, r1, 24, 20);
	S6(r2, r3, r4, r1, r0); store_and_load_keys(r4, r0, r3, r1, 20, 16);
	S7(r4, r0, r3, r1, r2); store_and_load_keys(r2, r3, r1, r4, 16, 12);
	S0(r2, r3, r1, r4, r0); store_and_load_keys(r1, r3, r4, r2, 12, 8);
	S1(r1, r3, r4, r2, r0); store_and_load_keys(r0, r4, r2, r1, 8, 4);
	S2(r0, r4, r2, r1, r3); store_and_load_keys(r3, r4, r0, r1, 4, 0);
	S3(r3, r4, r0, r1, r2); storekeys(r1, r2, r4, r3, 0);
}