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
typedef  int u32 ;

/* Variables and functions */
 int P1024e (int) ; 
 int P1024o (int) ; 
 int P128e (int) ; 
 int P128o (int) ; 
 int P16e (int) ; 
 int P16o (int) ; 
 int P1e (int) ; 
 int P1o (int) ; 
 int P2048e (int) ; 
 int P2048o (int) ; 
 int P256e (int) ; 
 int P256o (int) ; 
 int P2e (int) ; 
 int P2o (int) ; 
 int P32e (int) ; 
 int P32o (int) ; 
 int P4e (int) ; 
 int P4o (int) ; 
 int P512e (int) ; 
 int P512o (int) ; 
 int P64e (int) ; 
 int P64o (int) ; 
 int P8e (int) ; 
 int P8o (int) ; 

__attribute__((used)) static void gen_true_ecc(u8 *ecc_buf)
{
	u32 tmp = ecc_buf[0] | (ecc_buf[1] << 16) |
		((ecc_buf[2] & 0xF0) << 20) | ((ecc_buf[2] & 0x0F) << 8);

	ecc_buf[0] = ~(P64o(tmp) | P64e(tmp) | P32o(tmp) | P32e(tmp) |
			P16o(tmp) | P16e(tmp) | P8o(tmp) | P8e(tmp));
	ecc_buf[1] = ~(P1024o(tmp) | P1024e(tmp) | P512o(tmp) | P512e(tmp) |
			P256o(tmp) | P256e(tmp) | P128o(tmp) | P128e(tmp));
	ecc_buf[2] = ~(P4o(tmp) | P4e(tmp) | P2o(tmp) | P2e(tmp) | P1o(tmp) |
			P1e(tmp) | P2048o(tmp) | P2048e(tmp));
}