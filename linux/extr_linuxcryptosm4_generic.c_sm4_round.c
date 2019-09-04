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
typedef  int const u32 ;

/* Variables and functions */
 int const sm4_enc_sub (int const) ; 

__attribute__((used)) static u32 sm4_round(const u32 *x, const u32 rk)
{
	return x[0] ^ sm4_enc_sub(x[1] ^ x[2] ^ x[3] ^ rk);
}