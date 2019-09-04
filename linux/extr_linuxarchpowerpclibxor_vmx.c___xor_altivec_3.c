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
typedef  int /*<<< orphan*/  unative_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEFINE (int) ; 
 int /*<<< orphan*/  LOAD (int) ; 
 int /*<<< orphan*/  STORE (int) ; 
 int /*<<< orphan*/  XOR (int,int) ; 
 int v1 ; 
 int v2 ; 
 int v3 ; 

void __xor_altivec_3(unsigned long bytes, unsigned long *v1_in,
		     unsigned long *v2_in, unsigned long *v3_in)
{
	DEFINE(v1);
	DEFINE(v2);
	DEFINE(v3);
	unsigned long lines = bytes / (sizeof(unative_t)) / 4;

	do {
		LOAD(v1);
		LOAD(v2);
		LOAD(v3);
		XOR(v1, v2);
		XOR(v1, v3);
		STORE(v1);

		v1 += 4;
		v2 += 4;
		v3 += 4;
	} while (--lines > 0);
}